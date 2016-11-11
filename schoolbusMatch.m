clear all;close all;
%read in images
Ia=imread('School_bus1.bmp');
Ia2 = single(rgb2gray(Ia)) ;
Ib=imread('School_bus2.bmp');
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

%%%%%%%%%%%%%%%Compare%%%%%%%%%%%%%%%%
[fa, da] = vl_sift(Ia2) ;
[fb, db] = vl_sift(Ib2) ;
[matches, scores] = vl_ubcmatch(da, db) ;

figure ; clf ;
imagesc(cat(2, Ia, Ib)) ;

xa = fa(1,matches(1,:)) ;
xb = fb(1,matches(2,:)) + size(Ia,2) ;
ya = fa(2,matches(1,:)) ;
yb = fb(2,matches(2,:)) ;

hold on ;
h = line([xa ; xb], [ya ; yb]) ;
set(h,'linewidth', 1, 'color', 'b') ;

vl_plotframe(fa(:,matches(1,:))) ;
fb(1,:) = fb(1,:) + size(Ia,2) ;
vl_plotframe(fb(:,matches(2,:))) ;
axis image off ;


