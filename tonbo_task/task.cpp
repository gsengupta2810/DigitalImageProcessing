#include <opencv2/opencv.hpp>
#include <iostream>
#include <bits/stdc++.h>
using namespace cv;
using namespace std;

struct eq
{
	int l;
	vector<int> equivalents;
};

vector<eq> equiv;

void print_eq()
{
	for (int i = 0; i < equiv.size(); ++i)
	{
		cout<<equiv[i].l<<" ------> ";
		for (int j = 0; j < equiv[i].equivalents.size(); ++j)
		{
			cout<<(int)equiv[i].equivalents[j]<<" ";
		}
		cout<<endl;
	}
}

void blob_detect(unsigned char** img,int rows,int cols)
{
	
	int** visited;
	visited=new int*[rows];
	for (int i = 0; i < rows; ++i)
	{
		visited[i]=new int[cols];
		for (int j = 0; j < cols; ++j)
		{
			visited[i][j]=-1;
		}
	}
	int labels=0;

	for (int i = 1; i < rows-1; ++i)
	{
		for (int j = 1; j < cols-1 ; ++j)
		{
			if(img[i][j]==255 && visited[i][j]==-1)
			{
				// cout<<"1"<<endl;
				if(visited[i-1][j]==-1 && visited[i][j-1]==-1 )
				{
					// cout<<"------------------ 2 -----------------"<<labels<<endl;
					labels++;
					visited[i][j]=labels;
				}
				else if(visited[i-1][j]!=-1 && visited[i][j-1]==-1)
				{
					// cout<<"3"<<endl;
					visited[i][j]=visited[i-1][j];
				}
				else if(visited[i-1][j]==-1 && visited[i][j-1]!=-1)
				{
					// cout<<"4"<<endl;
					visited[i][j]=visited[i][j-1];
				}
				else if( visited[i-1][j]!=-1 && visited[i][j-1]!=-1)
				{
					if(visited[i-1][j]==visited[i][j-1])
					{
						// cout<<"10"<<endl;
						visited[i][j]=visited[i][j-1];
					}
					else if(visited[i-1][j]!= visited[i][j-1])
					{
						// cout<<"11"<<endl;
						int one=visited[i-1][j],two=visited[i][j-1];
						// cout<<"one = "<<one<<" , two ="<<two<<endl;
						bool there;
						if(equiv.size()==0)
						{
							int min,not_min;
							if(one<two)
							{
								min=one;
								not_min=two;
							}
							else
							{
								min=two;
								not_min=one;
							}
							// cout<<"12"<<endl;
							eq e;
							e.l=min;
							e.equivalents.push_back(not_min);
							equiv.push_back(e);
						}
						else
						{
							// cout<<"13"<<endl;
							if(one<two)
							{
								// cout<<"14"<<endl;
								visited[i][j]=one;
								for (int k = 0; k < equiv.size(); ++k)
								{
									if(one==equiv[k].l)
									{
										there=true;
										bool there_1=false;
										for (int l = 0; l < equiv[k].equivalents.size(); ++l)
										{
											if(equiv[k].equivalents[l]==two)
												there_1=true;
										}
										if(there_1==false)
										{
											equiv[k].equivalents.push_back(two);
										}
									}
									else
									{
										for (int l = 0; l < equiv[k].equivalents.size(); ++l)
										{
											if(equiv[k].equivalents[l]==one)
											{
												there=true;
												bool there_2=false;
												for (int l = 0; l < equiv[k].equivalents.size(); ++l)
												{
													if(equiv[k].equivalents[l]==two)
													{
														there_2=true;
													}
												}
												if(there_2==false)
												{
													equiv[k].equivalents.push_back(two);	
												}
											}
										}
									}
								}
								if(there==false)
								{
									eq e;
									e.l=one;
									e.equivalents.push_back(two);
									equiv.push_back(e);
								}
							}
							else
							{
								// cout<<"15"<<endl;
								visited[i][j]=two;
								for (int k = 0; k < equiv.size(); ++k)
								{
									if(two==equiv[k].l)
									{
										there=true;
										bool there_1=false;
										for (int l = 0; l < equiv[k].equivalents.size(); ++l)
										{
											if(equiv[k].equivalents[l]==one)
												there_1=true;
										}
										if(there_1==false)
										{
											equiv[k].equivalents.push_back(one);
										}
									}
									else
									{
										for (int l = 0; l < equiv[k].equivalents.size(); ++l)
										{
											if(equiv[k].equivalents[l]==two)
											{
												there=true;
												bool there_2=false;
												for (int l = 0; l < equiv[k].equivalents.size(); ++l)
												{
													if(equiv[k].equivalents[l]==one)
													{
														there_2=true;
													}
												}
												if(there_2==false)
												{
													equiv[k].equivalents.push_back(one);	
												}
											}
										}
									}
								}
								if(there==false)
								{
									eq e;
									e.l=two;
									e.equivalents.push_back(one);
									equiv.push_back(e);
								}
							}
						}
						
					}
					
				}
			}
		}
	}
	Mat blobs(rows,cols,CV_8UC3,Scalar(0,0,0));

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if(visited[i][j]!=-1)
			{
				int pos_label=visited[i][j];
				for (int k = 0; k < equiv.size(); ++k)
				{
					if(equiv[k].l!=pos_label)
					{
						for (int l = 0; l < equiv[k].equivalents.size(); ++l)
						{
							if(pos_label==equiv[k].equivalents[l])
							{
								visited[i][j]=equiv[k].l;
								blobs.at<Vec3b>(i,j)[0]=255/(visited[i][j]/50+1);
								blobs.at<Vec3b>(i,j)[1]=255/(visited[i][j]+visited[i][j]%50);
								blobs.at<Vec3b>(i,j)[2]=255/(visited[i][j]+(visited[i][j]/50)%50);
							}
							else
							{
								blobs.at<Vec3b>(i,j)[0]=255/(visited[i][j]/50+1);
								blobs.at<Vec3b>(i,j)[1]=255/(visited[i][j]+visited[i][j]%50);
								blobs.at<Vec3b>(i,j)[2]=255/(visited[i][j]+(visited[i][j]/50)%50);
							}
						}
					}
					else
					{
						blobs.at<Vec3b>(i,j)[0]=255/(visited[i][j]/50+1);
						blobs.at<Vec3b>(i,j)[1]=255/(visited[i][j]+visited[i][j]%50);
						blobs.at<Vec3b>(i,j)[2]=255/(visited[i][j]+(visited[i][j]/50)%50);
					}
				}
			}
		}
	}
	
	imshow("colored blobs",blobs);
}
Mat binarize(const Mat img)
{
	Mat img_binary(img.rows,img.cols,CV_8UC1,Scalar(0));
	for (int i = 0; i < img.rows; ++i)
	{
		for (int j = 0; j < img.cols ; ++j)
		{
			if(img.at<uchar>(i,j)>100)
				img_binary.at<uchar>(i,j)=255;
		}
	}
	imshow("binary",img_binary);
	return img_binary;
}
int main(int argc,char** argv)
{
	if(argc<2)
	{
		cout<<"enter the image path"<<endl;
	    return 0;
	}

	unsigned char **image;
	Mat img=imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	imshow("blobs",img);

	Mat binary=binarize(img);
	
	image=new unsigned char*[img.rows];

	for (int i = 0; i < img.rows; ++i)
	{
		image[i]=new unsigned char[img.cols];
		for (int j = 0; j < img.cols; ++j)
		{
			image[i][j]=binary.at<uchar>(i,j);
		}
	}
	
	blob_detect(image,img.rows,img.cols);
	waitKey(0);
}