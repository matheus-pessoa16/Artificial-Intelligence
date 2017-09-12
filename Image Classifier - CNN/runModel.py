												#################################################
												#   TRABALHO FINAL: INTELIGÊNCIA ARTIFICIAL		#
												#												#
												# ALUNOS: VICTOR CORTEZ E MATHEUS ESTEVAM		#
												# PROFESSOR: MARCELO AUGUSTO					#
												# 												#
												#												#
												# REDES CONVOLUTIVAS - CLASSIFICADOR DE IMAGENS	#
												#												#		
												#												#
												#################################################



from keras.datasets import cifar10 # subroutines for fetching the CIFAR-10 dataset
from keras.models import Sequential
from keras.layers import Dense
from keras.models import model_from_json
import numpy as np
from keras.utils import np_utils # utilities for one-hot encoding of ground truth values
from scipy import misc
from PIL import Image, ImageFilter, ImageFont, ImageDraw
from keras.preprocessing import image as image_utils
import os
import glob

list_class = ["barco", "carro", "caminhao", "aviao"]


def write_txt_img(img, text):
    # image = img
	image=img.convert("RGBA")
	txt = Image.new("RGBA", image.size, (255, 255, 255, 0))
	fnt = ImageFont.truetype('Pillow/Tests/fonts/FreeMono.ttf', 40)
	d = ImageDraw.Draw(txt)
	d.text((10, 10), text, font=fnt, fill=(255,69,0, 255))
	image_out = Image.alpha_composite(image, txt)
	image_out.show()


def class_name(predictions):
	for i in predictions:
		for x in range(0, len(i)):
			if i[x] == 1:	
				print("\n", list_class[x])
				result = [x, list_class[x]]				
				return result


# load json and create model
json_file = open('model.json', 'r')
loaded_model_json = json_file.read()
json_file.close()
loaded_model = model_from_json(loaded_model_json)
loaded_model.compile(loss='categorical_crossentropy', optimizer='adam', metrics=['accuracy'])
# load weights into new model
loaded_model.load_weights("model.h5")
print("Loaded model from disk")

file_list = glob.glob("*.png")
print(file_list)
name = []
for f in file_list:
	name.append(str(f))


image = []
original = []

for n in name:
	img = image_utils.load_img(n, target_size=(32, 32))
	print(n)
	original.append(Image.open(str(n)))
	img = image_utils.img_to_array(img)
	img = np.expand_dims(img, axis=0)
	image.append(img)	


predictions = []
res = []

for i in image:
	pred = (loaded_model.predict(i))
	print("\n")	
	print(pred)
	print("\n")	
	predictions.append(pred)
	res.append(class_name(pred))
	

# evaluate loaded model on test data
score = []
scr_txt = []



c = 0

for i in image:
	y = c
	y = np_utils.to_categorical(y, 4) # One-hot encode the labels
	scr = loaded_model.evaluate(i, y, verbose=0)
	# print("\n%s: %.2f%%\n" % (loaded_model.metrics_names[1], scr[1] * 100))
	scr_txt.append(scr[1] * 100)
	score.append(scr)
	c += 1


# print("%s: %.2f%%" % (loaded_model.metrics_names, score * 100))

size = [320, 240]
for i in range(0, len(res)):
	print(res[i][0])	
	g = original[res[i][0]]
	out = g.resize(size, Image.ANTIALIAS)
	s = str(res[i][1])
	write_txt_img(out, s)
	















