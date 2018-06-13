import matplotlib.pyplot as plt
import numpy as np 
import pandas as pd 
import seaborn as sns

def plot_psnr():
	df=pd.read_csv("./PSNR.csv")
	sns.pointplot(x="image", y="PSNR_value", data=df)
	plt.xlabel("image type")
	plt.ylabel("PNSR value")
	plt.savefig("./output/PSNR.jpg")
plot_psnr()