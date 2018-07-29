# Qt interface for the digital images processing
This interface has all the options seen in the basic course for the image processing.

Features
-------------

### Color transformation 
The application allows to transfom the format of the RGB images.
* RGB to HSL
* RGB to HSV

### Noise filters
This feature only applies for gray scale images. Has been implemented the basic filters: 
* Mean
* Median
* Gaussian 

### Histograms
This feature only applies for gray scale images. If you want to generate a equalized histogram you have to generate a simple histogram first. With a equalized histogram is easy to generate a equalized image. 
* Simple histogram
* Equalized histogram 
* Equalized image

### Thresholding
This feature only applies for gray scale images. Has been implemented the basic filters: 
* Isodata
* Otsu

### Morphological 
The structural element is a 7x7 square. This feature only applies for gray scale images. Has been implemented the basic operators:
* Erosion
* Dilate
* Opening
* Closing 

> Note: If you want to apply the features avaliable only for gray scale images to RGB images, you have to separate and apply the operation to evey channel individually and then, mix them in a new image with the RGB format.