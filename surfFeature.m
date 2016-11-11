%Only the version of Matlab is 2014 or later
%can run the function "detectSURFFeatures"
clear all;close all;
I = imread('Bus.bmp');
points = detectSURFFeatures(I);
figure,imshow(I); hold on;
plot(points.selectStrongest(50));

I = imread('Sedan.bmp');
points = detectSURFFeatures(I);
figure,imshow(I); hold on;
plot(points.selectStrongest(50));