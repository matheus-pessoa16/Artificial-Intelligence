# Machine Learning - Python scikit-learn - PCA


# import the datasets
from sklearn import datasets, cluster, metrics
import matplotlib.pyplot as plt
import numpy as np
from sklearn.decomposition import PCA, RandomizedPCA
from sklearn.preprocessing import scale
from sklearn.cross_validation import train_test_split
from sklearn.manifold import Isomap
from sklearn.metrics import homogeneity_score, completeness_score, v_measure_score, adjusted_rand_score, adjusted_mutual_info_score, silhouette_score

# load the dataset in the digits
digits = datasets.load_digits()

# print digits
print(digits)

# gets the keys of the digits
print(digits.keys())

# print out the data
print(digits.data)

# print out the target values
print(digits.target)

# print out the description of the 'digits'
print(digits.DESCR)


# isolate the data
digits_data = digits.data

# inspect the shape
print(digits_data.shape)

# isolate the target values
digits_target = digits.target

# inspect the shape
print(digits_target.shape)

# print the number of unique labels
number_digits = len(np.unique(digits_target))

# isolate the images
digits_images = digits.images

# inspect the shape
print(digits_images.shape)

# printing the images with matplotlib
# figure size (w, h) in inches
fig = plt.figure(figsize=(6 ,6))

# adjust the subplot
fig.subplots_adjust(left=0, right=1, bottom=0, top=1, hspace=0.05, wspace=0.05)

#for each of the 64 images
for i in range(64):
	# add a subplot in the grid of 8 by 8, at the i+1-th position 
	ax = fig.add_subplot(8, 8, i+1, xticks=[], yticks=[])
	# display an image at the i-th position
	ax.imshow(digits.images[i], cmap=plt.cm.binary, interpolation='bessel')
	# label the image with the target value
	ax.text(0, 7, str(digits.target[i]))

# show the plot
plt.show()

# create a randomized PCA model that takes two components
randomized_pca = RandomizedPCA(n_components=2)

# fit and transform the data to the model
reduced_data_rpca = randomized_pca.fit_transform(digits.data)

# create a regular PCA model
pca = PCA(n_components=2)

#fit and transform the data to the model
reduced_data_pca = pca.fit_transform(digits.data)

# inspect the shape
print(reduced_data_pca.shape)

# print out the data
print(reduced_data_rpca)
print(reduced_data_pca)

colors = ['black', 'blue', 'purple', 'yellow', 'white', 'red', 'lime', 'cyan', 'orange', 'gray']

for i in range(len(colors)):
	x = reduced_data_rpca[:, 0][digits.target == i]
	y = reduced_data_rpca[:, 1][digits.target == i]
	plt.scatter(x, y, c=colors[i])

plt.legend(digits.target_names, bbox_to_anchor=(1.05, 1), loc=2, borderaxespad=0.)
plt.xlabel('First Pricipal Component')
plt.ylabel('Second Pricipal Component') 
plt.title('PCA Scatter Plot')
plt.show()

