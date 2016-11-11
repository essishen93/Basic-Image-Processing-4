clear all;close all;
%read in images
Ia  = imread('Bus.bmp');        Ia2 = single(rgb2gray(Ia)) ;
Ib  = imread('Sedan.bmp');      Ib2 = single(rgb2gray(Ib)) ;
Ic  = imread('School_bus1.bmp');Ic2 = single(rgb2gray(Ic)) ;
Id  = imread('School_bus2.bmp');Id2 = single(rgb2gray(Id)) ;

%SIFT
[fa, da] = vl_sift(Ia2) ;
[fb, db] = vl_sift(Ib2) ;
[fc, dc] = vl_sift(Ic2) ;
[fd, dd] = vl_sift(Id2) ;

%kmeans clustering
X = [da,db,dc,dd];
data = double(X);
numClusters = 8;
[centers, assignments] = vl_kmeans(data, numClusters);

%Euclidean distance
dis=zeros(128,8);
sum_dis=zeros(1,8);

codebook1=zeros(1,8);
codebook2=zeros(1,8);
codebook3=zeros(1,8);
codebook4=zeros(1,8);
sample1=double(da);
sample2=double(db);
sample3=double(dc);
sample4=double(dd);

%compute the histogram of "Bus"
for j=1:size(sample1,2)
    for k=1:8
        dis(:,k)=(sample1(:,j)-centers(:,k)).^2;
        sum_dis(k)=sum(dis(:,k));
    end
    srt_dis=sort(sum_dis);
    for n=1:8
        if sum_dis(n)==srt_dis(1)
            codebook1(n)=codebook1(n)+1;
        end
    end
end

dis=zeros(128,8);sum_dis=zeros(1,8);
%compute the histogram of "Sedan"
for j=1:size(sample2,2)
    for k=1:8
        dis(:,k)=(sample2(:,j)-centers(:,k)).^2;
        sum_dis(k)=sum(dis(:,k));
    end
    srt_dis=sort(sum_dis);
    for n=1:8
        if sum_dis(n)==srt_dis(1)
            codebook2(n)=codebook2(n)+1;
        end
    end
end

dis=zeros(128,8);sum_dis=zeros(1,8);
%compute the histogram of "Sedan"
for j=1:size(sample3,2)
    for k=1:8
        dis(:,k)=(sample3(:,j)-centers(:,k)).^2;
        sum_dis(k)=sum(dis(:,k));
    end
    srt_dis=sort(sum_dis);
    for n=1:8
        if sum_dis(n)==srt_dis(1)
            codebook3(n)=codebook3(n)+1;
        end
    end
end


dis=zeros(128,8);sum_dis=zeros(1,8);
%compute the histogram of "Sedan"
for j=1:size(sample4,2)
    for k=1:8
        dis(:,k)=(sample4(:,j)-centers(:,k)).^2;
        sum_dis(k)=sum(dis(:,k));
    end
    srt_dis=sort(sum_dis);
    for n=1:8
        if sum_dis(n)==srt_dis(1)
            codebook4(n)=codebook4(n)+1;
        end
    end
end