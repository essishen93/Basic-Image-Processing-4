clear all;close all;
%read in images
Ia=imread('Bus.bmp');
Ia2 = single(rgb2gray(Ia)) ;
Ib=imread('Sedan.bmp');
Ib2 = single(rgb2gray(Ib)) ;

%%%%%%%%%%%%%%Bus%%%%%%%%%%%%%%%%%%%%%%

figure,image(Ia) ;
%compute the SIFT frames (keypoints)
[f,d] = vl_sift(Ia2) ;
%visualize a random selection of 50 features
perm = randperm(size(f,2)) ;
sel = perm(1:50) ;
h1 = vl_plotframe(f(:,sel)) ;
h2 = vl_plotframe(f(:,sel)) ;
set(h1,'color','k','linewidth',3) ;
set(h2,'color','y','linewidth',2) ;
%overlay the descriptors
figure,image(Ia) ;
h3 = vl_plotsiftdescriptor(d(:,sel),f(:,sel)) ;
set(h3,'color','g') ;

%%%%%%%%%%%%%%Sedan%%%%%%%%%%%%%%%%%%%%%%

figure,image(Ib) ;
%compute the SIFT frames (keypoints)
[f,d] = vl_sift(Ib2) ;
%visualize a random selection of 50 features
perm = randperm(size(f,2)) ;
sel = perm(1:50) ;
h1 = vl_plotframe(f(:,sel)) ;
h2 = vl_plotframe(f(:,sel)) ;
set(h1,'color','k','linewidth',3) ;
set(h2,'color','y','linewidth',2) ;
%overlay the descriptors
figure,image(Ib) ;
h3 = vl_plotsiftdescriptor(d(:,sel),f(:,sel)) ;
set(h3,'color','g') ;


