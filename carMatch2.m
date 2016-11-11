clear all;close all;
%read in images
Ia=imread('School_bus1.bmp');
Ia2 = single(rgb2gray(Ia)) ;
Ib=imread('Sedan3.bmp');
Ib2 = single(rgb2gray(Ib)) ;

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


