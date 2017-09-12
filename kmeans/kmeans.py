# Machine Learning - Python scikit-learn - KMeans


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


# apply scale() to the digits data
data = scale(digits.data)

# split the digits into training set and test set

X_train, X_test, y_train, y_test, images_train, images_test = train_test_split(data, digits.target, 
												digits.images, test_size=0.25, random_state=42)


n_samples, n_features = X_train.shape

# print out n_samples
print(n_samples)

# print out n_features
print(n_features)

# number of training labels
n_digits = len(np.unique(y_train))

print(len(y_train))

# create the KMeans model
clf = cluster.KMeans(init='k-means++', n_clusters=10, random_state=42)

# fit the training set to the model
clf.fit(X_train)

# figure size
fig = plt.figure(figsize=(8, 3))

# add title
fig.suptitle('Cluster Center Images', fontsize=14, fontweight='bold')

# for all labels (0-9)
for i in range(10):
	# initialize the subplot in a grid 2x5, at i+1th position
	ax = fig.add_subplot(2, 5, 1+i)
	#display images
	ax.imshow(clf.cluster_centers_[i].reshape((8, 8)), cmap=plt.cm.binary)
	# dont show the axes
	plt.axis('off')

plt.show()	

# predict the labels for 'X_test'
y_pred = clf.predict(X_test)

# print out the first 100 instanes of y_pred
print(y_pred[:100])

# print out the first 100 instanes of y_test
print(y_test[:100])

# inspect the shape
print(clf.cluster_centers_.shape)

# create a isomap and fit the data to it
X_iso = Isomap(n_neighbors=10).fit_transform(X_train)

# compute clusters centers and predict cluster index for each sample
clusters = clf.fit_predict(X_train)

# create a plot with subplots in a grid of 1x2
fig, ax = plt.subplots(1, 2, figsize=(8, 4))

# adjust layout
fig.suptitle('Predicted X Training Labels', fontsize=14, fontweight='bold')
fig.subplots_adjust(top=0.85)

# add scatterplots to the subplots
ax[0].scatter(X_iso[:, 0], X_iso[:, 1], c=clusters)
ax[0].set_title('Predicted Training Labels')
ax[1].scatter(X_iso[:, 0], X_iso[:, 1], c=y_train)
ax[0].set_title('Actual Training Labels')

plt.show()

print(metrics.confusion_matrix(y_test, y_pred))

print('% 9s' % 'inertia    homo   compl  v-meas     ARI AMI  silhouette')
print('%i   %.3f   %.3f   %.3f   %.3f   %.3f    %.3f'
          %(clf.inertia_,
      homogeneity_score(y_test, y_pred),
      completeness_score(y_test, y_pred),
      v_measure_score(y_test, y_pred),
      adjusted_rand_score(y_test, y_pred),
      adjusted_mutual_info_score(y_test, y_pred),
      silhouette_score(X_test, y_pred, metric='euclidean')))

