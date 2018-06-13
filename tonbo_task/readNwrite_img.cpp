#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <deque>

#define PNG_DEBUG 3
#include <png.h>

using namespace std;

struct Point
{
    int x;
    int y;
    Point(int a,int b)
    {
        x=a;
        y=b;
    }
};

void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void read_png_file(char* file_name)
{
        char header[8];    // 8 is the maximum size that can be checked

        /* open file and test for it being a png */
        FILE *fp = fopen(file_name, "rb");
        if (!fp)
                abort_("[read_png_file] File %s could not be opened for reading", file_name);
        fread(header, 1, 8, fp);
        // if (png_sig_cmp(header, 0, 8))
        //         abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);


        /* initialize stuff */
        png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[read_png_file] png_create_read_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[read_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during init_io");

        png_init_io(png_ptr, fp);
        png_set_sig_bytes(png_ptr, 8);

        png_read_info(png_ptr, info_ptr);

        width = png_get_image_width(png_ptr, info_ptr);
        height = png_get_image_height(png_ptr, info_ptr);
        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        number_of_passes = png_set_interlace_handling(png_ptr);
        png_read_update_info(png_ptr, info_ptr);


        /* read file */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[read_png_file] Error during read_image");

        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));

        png_read_image(png_ptr, row_pointers);

        fclose(fp);
}


void write_png_file(char* file_name)
{
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

        png_init_io(png_ptr, fp);


        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, color_type, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        png_write_image(png_ptr, row_pointers);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        for (y=0; y<height; y++)
                free(row_pointers[y]);
        free(row_pointers);

        fclose(fp);
}


void process_file(void)
{
     if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
                cout<<"RGB image"<<endl;

     if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_GRAY)
                cout<<"Gray image"<<endl;

        // if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
        //         abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
        //                "(lacks the alpha channel)");

        // if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
        //         abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
        //                PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));

        int** visited;
        visited=new int*[height];
        for (int i = 0; i < height; ++i)
        {
            visited[i]=new int[width];
        }
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                visited[i][j]=-1;
            }
        }

#define GRAY
#ifdef RGBA
        deque<Point> q;
        int count=1;
        for (y=1; y<height-1; y++) 
        {
            png_byte* row = row_pointers[y];
            for (x=1; x<width-1; x++)
            {
                png_byte* ptr = &(row[x*4]);
                printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                       x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
                int val=0.299*ptr[0] + 0.587*ptr[1] + 0.114*ptr[2];
                if(val>100)
                    val=255;
                else val=0;
                // printf("Pixel at position [ %d - %d ] has Gray value: %d \n",y, x,val);
//#############################################################################################
//                                  Blob Detection 
//#############################################################################################

                if(val==255 && visited[y][x]==-1 && (y!=0 && x!=0))
                {
                    // cout<<"1"<<endl;
                    int m=y,n=x;
                    q.push_back(Point(m,n));
                    visited[m][n]=0;
                    while(1)
                    {
                        // cout<<"entered while"<<endl;
                        for(int k=-1;k<2;k++)
                        {
                            for (int l = -1; l < 2; ++l)
                            {
                                png_byte* row_= row_pointers[y+k];
                                png_byte* ptr = &(row[(x+l)*4]);

                                int val_=0.299*ptr[0] + 0.587*ptr[1] + 0.114*ptr[2];
                                if(val_>100)
                                    val_=255;
                                else val_=0;
                                // printf("Pixel at position [ %d - %d ] has Gray value: %d \n",m+k, n+l,val_);
                                // cout<<"m = "<<m<<" , n = "<<n<<endl;
                                // cout<<"m+k = "<<m+k<<" , n+l = "<<n+l<<endl;
                                if((m>0 && m<height-1) && (n>0 && n<width-1) && val_==255 && visited[m+k][n+l]==-1)
                                {
                                    cout<<" in "<<endl;
                                    q.push_back(Point(m+k,n+l));
                                    visited[m+k][n+l]=0;
                                    cout<<" out "<<endl;
                                }
                            }
                        }
                        // cout<<"2"<<endl;
                        if((m>0 && m<height-1) && (n>0 && n<width-1))
                            visited[q.front().x][q.front().y]=count;

                        q.pop_front();
                        if(q.empty()!=true)
                        {
                            // cout<<"looping while"<<endl;
                            // cout<<"q size = "<<q.size()<<" ||||| q top = "<<q.front().x<<","<<q.front().y<<endl;
                            m=q.front().x;
                            n=q.front().y;
                        }
                        else 
                        {
                            cout<<"breaking while"<<endl;
                            break;
                        }
                    }
                    cout<<"3"<<endl;
                    count++;
                }
                cout<<"!!!!!!!!!!!!!!!! Number of Blobs =  "<<count<<" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
//#############################################################################################
//                                  Blob Detection Complete
//#############################################################################################
#endif

#ifdef GRAY
        cout<<"here"<<endl;
        deque<Point> q;
        int count=1;
        for (y=1; y<height-1; y++) 
        {
            png_byte* row = row_pointers[y];
            for (x=1; x<width-1; x++)
            {
                png_byte* ptr = &(row[x*1]);
                // printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                //        x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
                int val=ptr[0];
                // if(val>100)
                //     val=255;
                // else val=0;
                // printf("Pixel at position [ %d - %d ] has Gray value: %d \n",y, x,val);

//#############################################################################################
//                                  Blob Detection 
//#############################################################################################

                if(val==255 && visited[y][x]==-1 && (y!=0 && x!=0))
                {
                    // cout<<"1"<<endl;
                    int m=y,n=x;
                    q.push_back(Point(m,n));
                    visited[m][n]=0;
                    while(1)
                    {
                        // cout<<"entered while"<<endl;
                        for(int k=-1;k<2;k++)
                        {
                            for (int l = -1; l < 2; ++l)
                            {
                                png_byte* row_= row_pointers[y+k];
                                png_byte* ptr = &(row[(x+l)*4]);

                                int val_=ptr[0];
                                // printf("Pixel at position [ %d - %d ] has Gray value: %d \n",m+k, n+l,val_);
                                // cout<<"m = "<<m<<" , n = "<<n<<endl;
                                // cout<<"m+k = "<<m+k<<" , n+l = "<<n+l<<endl;
                                if((m>0 && m<height-1) && (n>0 && n<width-1) && val_==255 && visited[m+k][n+l]==-1)
                                {
                                    // cout<<" in "<<endl;
                                    q.push_back(Point(m+k,n+l));
                                    visited[m+k][n+l]=0;
                                    // cout<<" out "<<endl;
                                }
                            }
                        }
                        // cout<<"2"<<endl;
                        visited[q.front().x][q.front().y]=count;
                        q.pop_front();
                        if(q.empty()!=true)
                        {
                            // cout<<"looping while"<<endl;
                            // cout<<"q size = "<<q.size()<<" ||||| q top = "<<q.front().x<<","<<q.front().y<<endl;
                            m=q.front().x;
                            n=q.front().y;
                        }
                        else 
                        {
                            // cout<<"breaking while"<<endl;
                            break;
                        }
                    }
                    // cout<<"3"<<endl;
                    count++;
                }
                // cout<<"!!!!!!!!!!!!!!!! Number of Blobs =  "<<count<<" !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
//#############################################################################################
//                                  Blob Detection Complete
//#############################################################################################
#endif

                /* set red value to 0 and green value to the blue one */
                ptr[0] = 0;
                ptr[1] = ptr[2];
            }
        }
        cout<<count<<endl;
}


int main(int argc, char **argv)
{
        if (argc != 3)
                abort_("Usage: program_name <file_in> <file_out>");

        read_png_file(argv[1]);
        process_file();
        write_png_file(argv[2]);

        return 0;
}