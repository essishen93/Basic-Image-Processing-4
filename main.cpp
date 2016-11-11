//Name: Maoru Shen
//USC ID Number: 4946-8507-13
//USC Email: maorushe@usc.edu
//Submission Date: 11/29/2015
////////////////////////////////////////////////////////////////////
//Problem 1 : (a)
//This code is to setup a decision tree of testing sample for OCR
/////////////////////////////////////////////////////////////////////
//main.cpp
/////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
//#include "functions.h"
using namespace std;

const int Size_H=256;    //the size of input image
const int Size_W=512;    //the size of input image
const int BytesPerPixel=3; //24-bit

int main()
{
    
    int pO=0,qO=0;    //the Image coordinate of output
    int pI=0,qI=0;    //the Image coordinate of input
    int c=0;          //channels
    
    unsigned char In_Image   [Size_H][Size_W][BytesPerPixel];         //the image data of input image
    unsigned char Bi_Image   [Size_H][Size_W];                        //the image data of input image in binary form
    unsigned char Label      [Size_H][Size_W]={0};                    //the label of object
    unsigned char Se_Image [Size_H][Size_W][BytesPerPixel]={0};      //the image data of output image after segmentation
    
    ///////////////Read image///////////////
    ifstream ifile("Training.raw",ios_base::in | ios_base::binary);
    if (!ifile)
    {
        cout<<"File CANNOT open!"<<endl;
        exit(1);
    }
    for (pI=0;pI<Size_H;pI++)
        for (qI=0;qI<Size_W;qI++)
            for (c=0;c<BytesPerPixel;c++)
            {
                ifile.read((char*)&In_Image[pI][qI][c],sizeof(In_Image[pI][qI][c]));
                if (c==0)
                {
                    if (In_Image[pI][qI][c]==255)
                        Bi_Image[pI][qI]=0;
                    else
                        Bi_Image[pI][qI]=1;
                }
                    
            }
    ifile.close();
    
   
    ///////////////Object Detection////////////////
    int neigh_value=0;     //checking the labels of neighbors
    int label=1;
    int min=0,temp=0;
    int link[85][85]={0};  //the label table
    int link_min[85]={0};  //the minimum label each label connects
    int j=0;
    for (pI=1;pI<Size_H-1;pI++)
        for (qI=1;qI<Size_W-1;qI++)
        {
            //non-background
            if (Bi_Image[pI][qI]==1)
            {
                neigh_value=Bi_Image[pI][qI-1]+Bi_Image[pI-1][qI-1]+Bi_Image[pI-1][qI]+Bi_Image[pI-1][qI+1];
                //surround by background
                if (neigh_value==0)
                {
                    Label[pI][qI]=label;
                    label++;
                }
                else
                {
                    //find the minimum label surrounded
                    if (Label[pI][qI-1]!=0)
                        min=Label[pI][qI-1];
                    if (Label[pI-1][qI-1]!=0)
                        min=Label[pI-1][qI-1];
                    if (Label[pI-1][qI]!=0)
                        min=Label[pI-1][qI];
                    if (Label[pI-1][qI+1]!=0)
                        min=Label[pI-1][qI+1];
                    
                    if  (Label[pI][qI-1]!=0)
                    {
                        temp=Label[pI][qI-1];
                        if (temp<min)
                            min=temp;
                    }
                    if  (Label[pI-1][qI-1]!=0)
                    {
                        temp=Label[pI-1][qI-1];
                        if (temp<min)
                            min=temp;
                    }
                    if  (Label[pI-1][qI]!=0)
                    {
                        temp=Label[pI-1][qI];
                        if (temp<min)
                            min=temp;
                    }
                    if  (Label[pI-1][qI+1]!=0)
                    {
                        temp=Label[pI-1][qI+1];
                        if (temp<min)
                            min=temp;
                    }
                    //minimum
                    Label[pI][qI]=min;
                    
                    //update the label tabel
                    if  (Label[pI][qI-1]!=0)
                    {
                        temp=Label[pI][qI-1];
                        link[min][temp]=1;
                        link[temp][min]=1;
                        
                    }
                    if  (Label[pI-1][qI-1]!=0)
                    {
                        temp=Label[pI-1][qI-1];
                        link[min][temp]=1;
                        link[temp][min]=1;
                    }
                    if  (Label[pI-1][qI]!=0)
                    {
                        temp=Label[pI-1][qI];
                        link[min][temp]=1;
                        link[temp][min]=1;
                    }
                    if  (Label[pI-1][qI+1]!=0)
                    {
                        temp=Label[pI-1][qI+1];
                        link[min][temp]=1;
                        link[temp][min]=1;
                    }
                    
                    
                }
            }
            
        }
    //cout<<label<<endl;
    
    //complete the label table
    for (pI=0;pI<85;pI++)
        for (qI=0;qI<85;qI++)
        {
            if (link[pI][qI]!=0)
            {
                for (j=0;j<85;j++)
                {
                    if (link[qI][j]!=0)
                    {
                        link[j][pI]=1;
                        link[pI][j]=1;
                    }
                }
                
            }
        }
    /*
    ofstream lbfile("label_objects_1.txt",ios_base::out);
    if (!lbfile)
    {
        cout<<"open failed"<<endl;
        exit(1);
    }
    
    for (pI=0;pI<85;pI++)
        for(qI=0;qI<85;qI++)
        {
            lbfile<<link[pI][qI];
            if (qI==84)
                lbfile<<endl;
            else
                lbfile<<" ";
        }
    lbfile.close();
    
    */
    //int obj=0;
    //find the minimum label each label connects
    for (pI=0;pI<85;pI++)
        for (qI=0;qI<85;)
        {
            if (link[pI][qI]!=0)
            {
                link_min[pI]=qI;
                //if (qI!=1)
                    //obj++;
                qI=85;
            }
            else
                qI++;
        }
    
    
    //label the object by different colors
    for (pO=0;pO<Size_H;pO++)
        for (qO=0;qO<Size_W;qO++)
        {
            if (link_min[Label[pO][qO]]==1)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=1; //S
            }
            
            else if (link_min[Label[pO][qO]]==2)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=2; //P
            }
            
            else if (link_min[Label[pO][qO]]==3)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=127;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=3; //E
            }
            
            else if (link_min[Label[pO][qO]]==4)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=127;
                Label[pO][qO]=4; //D
            }
            
            else if (link_min[Label[pO][qO]]==7)
            {
                Se_Image[pO][qO][0]=255;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=5; //L
            }
            
            else if (link_min[Label[pO][qO]]==8)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=6; //I
            }
            
            else if (link_min[Label[pO][qO]]==9)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=7; //M
            }
            
            else if (link_min[Label[pO][qO]]==11)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=127;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=8; //T
            }
            
            else if (link_min[Label[pO][qO]]==24)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=127;
                Label[pO][qO]=9; //0
            }
            
            else if (link_min[Label[pO][qO]]==25)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=127;
                Se_Image[pO][qO][2]=127;
                Label[pO][qO]=10; //1
            }
            
            else if (link_min[Label[pO][qO]]==26)
            {
                Se_Image[pO][qO][0]=255;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=11; //2
            }
            
            else if (link_min[Label[pO][qO]]==27)
            {
                Se_Image[pO][qO][0]=255;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=12; //3
            }
            
            else if (link_min[Label[pO][qO]]==34)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=13; //4
            }
            
            else if (link_min[Label[pO][qO]]==35)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=0;
                Label[pO][qO]=14; //5
            }
            
            else if (link_min[Label[pO][qO]]==28)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=0;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=15; //6
            }
            
            else if (link_min[Label[pO][qO]]==37)
            {
                Se_Image[pO][qO][0]=0;
                Se_Image[pO][qO][1]=127;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=16; //7
            }
            
            else if (link_min[Label[pO][qO]]==29)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=127;
                Se_Image[pO][qO][2]=127;
                Label[pO][qO]=17; //8
            }
            
            else if (link_min[Label[pO][qO]]==30)
            {
                Se_Image[pO][qO][0]=127;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=127;
                Label[pO][qO]=18; //9
            }
           
            else
            {
                Se_Image[pO][qO][0]=255;
                Se_Image[pO][qO][1]=255;
                Se_Image[pO][qO][2]=255;
                Label[pO][qO]=0;
            }
        }
    
    //int kk=0;
    ///////////////////Write image/////////////////////
    ofstream ofile("Segment_result.raw",ios_base::out | ios_base::binary);
    if (!ofile)
    {
        cout<<"open failed"<<endl;
        exit(1);
    }
    for (pO=0;pO<Size_H;pO++)
        for (qO=0;qO<Size_W;qO++)
        {
            for (c=0;c<BytesPerPixel;c++)
            {
                Se_Image[pO][qO][c]=Se_Image[pO][qO][c]+0x00;    //Convert to hex or bin
                ofile.write((char*)&Se_Image[pO][qO][c],sizeof(Se_Image[pO][qO][c]));
            }
        }
    ofile.close();
    
    ///////////////Segmentation///////////////
    int cord_size[19][4]={0};
    cord_size[ 1][0]=27; cord_size[ 1][1]=24; cord_size[ 1][2]=68; cord_size[ 1][3]=54; //S
    cord_size[ 2][0]=27; cord_size[ 2][1]=87; cord_size[ 2][2]=68; cord_size[ 2][3]=54; //P
    cord_size[ 3][0]=27; cord_size[ 3][1]=148;cord_size[ 3][2]=68; cord_size[ 3][3]=51; //E
    cord_size[ 4][0]=27; cord_size[ 4][1]=209;cord_size[ 4][2]=68; cord_size[ 4][3]=53; //D
    cord_size[ 5][0]=27; cord_size[ 5][1]=274;cord_size[ 5][2]=68; cord_size[ 5][3]=50; //L
    cord_size[ 6][0]=27; cord_size[ 6][1]=331;cord_size[ 6][2]=68; cord_size[ 6][3]=14; //I
    cord_size[ 7][0]=27; cord_size[ 7][1]=358;cord_size[ 7][2]=68; cord_size[ 7][3]=61; //M
    cord_size[ 8][0]=27; cord_size[ 8][1]=426;cord_size[ 8][2]=68; cord_size[ 8][3]=50; //T
    
    cord_size[ 9][0]=129;cord_size[ 9][1]=6;  cord_size[ 9][2]=68; cord_size[ 9][3]=45; //0
    cord_size[10][0]=129;cord_size[10][1]=62; cord_size[10][2]=68; cord_size[10][3]=32; //1
    cord_size[11][0]=129;cord_size[11][1]=108;cord_size[11][2]=68; cord_size[11][3]=44; //2
    cord_size[12][0]=129;cord_size[12][1]=158;cord_size[12][2]=68; cord_size[12][3]=46; //3
    cord_size[13][0]=129;cord_size[13][1]=209;cord_size[13][2]=68; cord_size[13][3]=47; //4
    cord_size[14][0]=129;cord_size[14][1]=260;cord_size[14][2]=68; cord_size[14][3]=46; //5
    cord_size[15][0]=129;cord_size[15][1]=312;cord_size[15][2]=68; cord_size[15][3]=45; //6
    cord_size[16][0]=129;cord_size[16][1]=362;cord_size[16][2]=68; cord_size[16][3]=46; //7
    cord_size[17][0]=129;cord_size[17][1]=414;cord_size[17][2]=68; cord_size[17][3]=44; //8
    cord_size[18][0]=129;cord_size[18][1]=465;cord_size[18][2]=68; cord_size[18][3]=44; //9
    
    ///////////////Feature Extraction///////////////

    //bit quads
    int bit_quads_1=0;
    int bit_quads_2=0;
    int bit_quads_3=0;
    int bit_quads_4=0;
    int bit_quads_d=0;
    int bit_value=0;
    
    //int bit_value_matrix[2][2]={0};
    
    int Eulr[19]={0};          //Euler number
    int Area[19]={0};          //Area
    int Peri=0;                //Perimeter
    double Circ[19]={0};       //Circularity
    double Symm_y[19][3]={0};  //Symmetry: left & right
    double Symm_x[19][3]={0};  //Symmetry: up & down
    int symm_axis_y=0;         //Symmetry axis
    int symm_axis_x=0;         //Symmetry axis
    
    //data of features of each object, including Euler number
    // int feature[19][3]={0};
    
    int lb=0;   //label
    
    //Hu's Moments
    int k=0;j=0;
    int m=0,n=0;
    double xj=0,yk=0;
    double x_j=0,y_k=0;
    //double xx=0,yy=0;
    double M[4][4]={0};
    double U[4][4]={0};
    double V[4][4]={0};
    double alpha=0;
    
    double Mnt_1[19]={0};//Moment 1
    double Mnt_2[19]={0};//Moment 2
    double Mnt_3[19]={0};//Moment 3
    double Mnt_4[19]={0};//Moment 4
    
    double horizon_max=0;
    double horizon_min=0;
    double horizon_value=0;
    int max_row[19]={0};
    int min_row[19]={0};
    
    for (lb=1;lb<19;lb++)
    {
        symm_axis_y=(int)cord_size[lb][3]/2;
        symm_axis_x=(int)cord_size[lb][2]/2;
        
        horizon_max=0;
        horizon_min=100;
        
        for (pI=cord_size[lb][0];pI<(cord_size[lb][0]+cord_size[lb][2]-1);pI++)
        {
            horizon_value=0;
            
            for (qI=cord_size[lb][1];qI<(cord_size[lb][1]+cord_size[lb][3]-1);qI++)
            {
                horizon_value+=Bi_Image[pI][qI];
                
                //compute the bits in 2X2 area
                bit_value=Bi_Image[pI][qI]+Bi_Image[pI][qI+1]+Bi_Image[pI+1][qI]+Bi_Image[pI+1][qI+1];
                
                if (bit_value==1)
                    bit_quads_1++;
                if (bit_value==3)
                    bit_quads_3++;
                if (bit_value==4)
                    bit_quads_4++;
                if (bit_value==2)
                {
                    if (Bi_Image[pI][qI]==Bi_Image[pI+1][qI+1])
                        bit_quads_d++;
                    else
                        bit_quads_2++;
                }
                
                //compute the values for symmetry (left & right)
                if (qI<(cord_size[lb][1]+symm_axis_y))
                    Symm_y[lb][0]+=Bi_Image[pI][qI];
                else
                    Symm_y[lb][1]+=Bi_Image[pI][qI];
                
                //compute the values for symmetry (up & down)
                if (pI<(cord_size[lb][0]+symm_axis_x))
                    Symm_x[lb][0]+=Bi_Image[pI][qI];
                else
                    Symm_x[lb][1]+=Bi_Image[pI][qI];
                
                //Moment: M matrix
                yk=(double)(pI-cord_size[lb][0])+0.5;xj=(double)(qI-cord_size[lb][1])+0.5;
                m=0;n=0;
                M[m][n]+=pow(xj,m)*pow(yk,n)*Bi_Image[pI][qI]/(pow(cord_size[lb][3],m)*pow(cord_size[lb][2],n));
                m=1;n=0;
                M[m][n]+=pow(xj,m)*pow(yk,n)*Bi_Image[pI][qI]/(pow(cord_size[lb][3],m)*pow(cord_size[lb][2],n));
                m=0;n=1;
                M[m][n]+=pow(xj,m)*pow(yk,n)*Bi_Image[pI][qI]/(pow(cord_size[lb][3],m)*pow(cord_size[lb][2],n));
                
            }
            
            if (horizon_value!=0 && horizon_value>horizon_max)
            {
                horizon_max=horizon_value;
                max_row[lb]=pI-cord_size[lb][0];
            }
            
            if (horizon_value!=0 && horizon_value<horizon_min)
            {
                horizon_min=horizon_value;
                min_row[lb]=pI-cord_size[lb][0];
            }
        }
        if (lb==1)
            cout<<"S"<<endl;
        if (lb==2)
            cout<<"P"<<endl;
        if (lb==3)
            cout<<"E"<<endl;
        if (lb==4)
            cout<<"D"<<endl;
        if (lb==5)
            cout<<"L"<<endl;
        if (lb==6)
            cout<<"I"<<endl;
        if (lb==7)
            cout<<"M"<<endl;
        if (lb==8)
            cout<<"T"<<endl;
        if (lb==9)
            cout<<"0"<<endl;
        if (lb==10)
            cout<<"1"<<endl;
        if (lb==11)
            cout<<"2"<<endl;
        if (lb==12)
            cout<<"3"<<endl;
        if (lb==13)
            cout<<"4"<<endl;
        if (lb==14)
            cout<<"5"<<endl;
        if (lb==15)
            cout<<"6"<<endl;
        if (lb==16)
            cout<<"7"<<endl;
        if (lb==17)
            cout<<"8"<<endl;
        if (lb==18)
            cout<<"9"<<endl;
        
        //compute the Euler number
        Eulr[lb]=(bit_quads_1-bit_quads_3+2*bit_quads_d)/4;
        
        //compute the Circularity
        Area[lb]=(bit_quads_1+2*bit_quads_2+3*bit_quads_3+4*bit_quads_4+2*bit_quads_d)/4;
        Peri=bit_quads_1+bit_quads_2+bit_quads_3+2*bit_quads_d;
        Circ[lb]=4*3.1415926*(double)Area[lb]/(double)(Peri*Peri);
        //Circ[lb]=(double)(Peri*Peri)/(4*3.1415926*(double)Area[lb]);
        
        cout<<"E: "<<Eulr[lb]<<endl;
        //cout<<"A: "<<Area<<endl;
        //cout<<"P: "<<Peri<<endl;
        //cout<<"C: "<<Circ<<endl;
        
        bit_quads_1=0;
        bit_quads_2=0;
        bit_quads_3=0;
        bit_quads_4=0;
        bit_quads_d=0;
        bit_value=0;
        
        x_j=M[1][0]/M[0][0];
        y_k=M[0][1]/M[0][0];
        
        for (j=cord_size[lb][0];j<=(cord_size[lb][0]+cord_size[lb][2]-1);j++)
            for (k=cord_size[lb][1];k<=(cord_size[lb][1]+cord_size[lb][3]-1);k++)
            {
                yk=(double)(j-cord_size[lb][0])+0.5;xj=(double)(k-cord_size[lb][1])+0.5;
                
                m=2;n=0;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=0;n=2;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=1;n=1;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=3;n=0;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=0;n=3;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=2;n=1;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                m=1;n=2;
                U[m][n]+=pow((xj-x_j),m)*pow((yk-y_k),n)*Bi_Image[j][k];
                
            }
        
        m=2;n=0;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=0;n=2;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=1;n=1;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=3;n=0;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=0;n=3;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=2;n=1;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        m=1;n=2;alpha=(double)(m+n)/2+1;
        V[m][n]=U[m][n]/pow(M[0][0],alpha);
        
        Mnt_1[lb]=V[2][0]+V[0][2];
        Mnt_2[lb]=(V[2][0]-V[0][2])*(V[2][0]-V[0][2])+4*V[1][1]*V[1][1];
        Mnt_3[lb]=(V[3][0]-3*V[1][2])*(V[3][0]-3*V[1][2])+(V[0][3]-3*V[2][1])*(V[0][3]-3*V[2][1]);
        Mnt_4[lb]=(V[3][0]+V[1][2])*(V[3][0]+V[1][2])+(V[0][3]-V[2][1])*(V[0][3]-V[2][1]);
        //cout<<"M1: "<<Mnt_1[lb]<<endl;
        //cout<<"M2: "<<Mnt_2[lb]<<endl;
        //cout<<"M3: "<<Mnt_3[lb]<<endl;
        
        
        
        for (j=0;j<4;j++)
            for (k=0;k<4;k++)
            {
                M[j][k]=0;
                U[j][k]=0;
                V[j][k]=0;
            }
        cout<<endl;
    }
    
    double amax=Area[1],amin=Area[2];
    double cmax=Circ[1],cmin=Circ[2];
    
    double m1_max=Mnt_1[1],m1_min=Mnt_1[2];
    double m2_max=Mnt_2[1],m2_min=Mnt_2[2];
    double m3_max=Mnt_3[1],m3_min=Mnt_3[2];
    double m4_max=Mnt_4[1],m4_min=Mnt_4[2];
    
    double as_rt_max=cord_size[ 1][3],as_rt_min=cord_size[ 2][3];
    
    double atemp=0,ctemp=0,m1_temp=0,m2_temp=0,m3_temp=0,m4_temp=0,as_rt_temp=0;
    for (lb=1;lb<19;lb++)
    {
        atemp=Area[lb];
        if (atemp>amax)
            amax=atemp;
        if (atemp<amin)
            amin=atemp;
        
        ctemp=Circ[lb];
        if (ctemp>cmax)
            cmax=ctemp;
        if (ctemp<cmin)
            cmin=ctemp;
        
        m1_temp=Mnt_1[lb];
        if (m1_temp>m1_max)
            m1_max=m1_temp;
        if (m1_temp<m1_min)
            m1_min=m1_temp;
        
        m2_temp=Mnt_2[lb];
        if (m2_temp>m2_max)
            m2_max=m2_temp;
        if (m2_temp<m2_min)
            m2_min=m2_temp;
        
        m3_temp=Mnt_3[lb];
        if (m3_temp>m3_max)
            m3_max=m3_temp;
        if (m3_temp<m3_min)
            m3_min=m3_temp;
        
        m4_temp=Mnt_4[lb];
        if (m4_temp>m4_max)
            m4_max=m4_temp;
        if (m4_temp<m4_min)
            m4_min=m4_temp;
        
        as_rt_temp=cord_size[lb][3];
        if (as_rt_temp>as_rt_max)
            as_rt_max=as_rt_temp;
        if (as_rt_temp<as_rt_min)
            as_rt_min=as_rt_temp;
    }
    
    //cout<<as_rt_min<<"  "<<as_rt_max<<endl;
    
    cout<<"Circularity"<<endl;
    for (lb=1;lb<19;lb++)
    {
        Circ[lb]=(Circ[lb]-cmin)/(cmax-cmin);
        cout<<Circ[lb]<<endl;
    }
    cout<<endl;
    
    double AsRt[19]={0};
    cout<<"Aspect Ratio"<<endl;
    for (lb=1;lb<19;lb++)
    {
        AsRt[lb]=(cord_size[lb][3]-as_rt_min)/(as_rt_max-as_rt_min);
        cout<<AsRt[lb]<<endl;
    }
    cout<<endl;
    
    cout<<"Symmetry1 (LR)"<<endl;
    for (lb=1;lb<19;lb++)
    {
        if (Symm_y[lb][0]<Symm_y[lb][1])
            Symm_y[lb][2]=Symm_y[lb][0]/Symm_y[lb][1];
        else
            Symm_y[lb][2]=Symm_y[lb][1]/Symm_y[lb][0];
        cout<<Symm_y[lb][2]<<endl;
    }
    cout<<endl;
    
    cout<<"Symmetry2 (UD)"<<endl;
    for (lb=1;lb<19;lb++)
    {
        if (Symm_x[lb][0]<Symm_x[lb][1])
            Symm_x[lb][2]=Symm_x[lb][0]/Symm_x[lb][1];
        else
            Symm_x[lb][2]=Symm_x[lb][1]/Symm_x[lb][0];
        cout<<Symm_x[lb][2]<<endl;
    }
    cout<<endl;
    
    cout<<"Moment 1"<<endl;
    for (lb=1;lb<19;lb++)
    {
        Mnt_1[lb]=(Mnt_1[lb]-m1_min)/(m1_max-m1_min);
        cout<<Mnt_1[lb]<<endl;
    }
    cout<<endl;
    
    cout<<"Moment 2"<<endl;
    for (lb=1;lb<19;lb++)
    {
        Mnt_2[lb]=(Mnt_2[lb]-m2_min)/(m2_max-m2_min);
        cout<<Mnt_2[lb]<<endl;
    }
    
    cout<<endl;
    
    cout<<"Moment 3"<<endl;
    for (lb=1;lb<19;lb++)
    {
        Mnt_3[lb]=(Mnt_3[lb]-m3_min)/(m3_max-m3_min);
        cout<<Mnt_3[lb]<<endl;
    }
    cout<<endl;
    
    cout<<"Moment 4"<<endl;
    for (lb=1;lb<19;lb++)
    {
        Mnt_4[lb]=(Mnt_4[lb]-m4_min)/(m4_max-m4_min);
        cout<<Mnt_4[lb]<<endl;
    }
    cout<<endl;
    
    cout<<"max row"<<endl;
    for (lb=1;lb<19;lb++)
    {
        if (max_row[lb]>(cord_size[lb][2]/2))
            cout<<"down"<<endl;
        else
            cout<<"up"<<endl;
    }
    cout<<endl;
    
    cout<<"min row"<<endl;
    for (lb=1;lb<19;lb++)
    {
        if (min_row[lb]>(cord_size[lb][2]/2))
            cout<<"down"<<endl;
        else
            cout<<"up"<<endl;
    }
    cout<<endl;
    
    
    //////////////Decision Tree/////////////////
    for (lb=1;lb<19;lb++)
    {
        if (Eulr[lb]==1)
        {
            if (Circ[lb]<0.4)
            {
                if (Symm_x[lb][2]<0.7)
                    cout<<"No."<<lb<<" character is 7"<<endl;
                else
                {
                    if (Symm_y[lb][2]<0.75)
                    {
                        if (Mnt_1[lb]<0.5)
                            cout<<"No."<<lb<<" character is E"<<endl;
                        else
                            cout<<"No."<<lb<<" character is 3"<<endl;
                    }
                    else
                    {
                        if (Mnt_1[lb]<0.5)
                        {
                            if (AsRt[lb]==1)
                                cout<<"No."<<lb<<" character is M"<<endl;
                            else
                                cout<<"No."<<lb<<" character is S"<<endl;
                        }
                        else
                        {
                            if (max_row[lb]<(cord_size[lb][2]/2))
                                cout<<"No."<<lb<<" character is 5"<<endl;
                            else
                                cout<<"No."<<lb<<" character is 2"<<endl;
                        }
                        
                    }
                    
                }
                
                
            }
            else
            {
                if (Symm_y[lb][2]<0.5)
                {
                    if (AsRt[lb]<0.5)
                        cout<<"No."<<lb<<" character is 1"<<endl;
                    else
                        cout<<"No."<<lb<<" character is L"<<endl;
                }
                else
                {
                    if (Mnt_1[lb]<0.7)
                        cout<<"No."<<lb<<" character is T"<<endl;
                    else
                        cout<<"No."<<lb<<" character is I"<<endl;
                }
                
            }
            
        }
        else if (Eulr[lb]==0)
        {
            if (Symm_x[lb][2]<0.65)
            {
                if (Mnt_1[lb]<0.5)
                    cout<<"No."<<lb<<" character is P"<<endl;
                else
                    cout<<"No."<<lb<<" character is 4"<<endl;
            }
            else
            {
                if (Symm_y[lb][2]>0.95)
                    cout<<"No."<<lb<<" character is 0"<<endl;
                else
                {
                    if (AsRt[lb]>0.75)
                        cout<<"No."<<lb<<" character is D"<<endl;
                    else
                    {
                        if (min_row[lb]<(cord_size[lb][2]/2))
                            cout<<"No."<<lb<<" character is 6"<<endl;
                        else
                            cout<<"No."<<lb<<" character is 9"<<endl;
                    }
                }
                
            }
            
        }
        else
            cout<<"No."<<lb<<" character is 8"<<endl;
    }
    
    
    /*
    //////////////Decision Tree/////////////////
    for (lb=1;lb<19;lb++)
    {
        if (Eulr[lb]==1)
        {
            if (Circ[lb]<0.5)
            {
                if (Symm_x[lb][2]<0.7)
                    cout<<"No."<<lb<<" character is 7"<<endl;
                else
                {
                    if (Symm_y[lb][2]<0.75)
                    {
                        if (Mnt_1[lb]<0.5)
                            cout<<"No."<<lb<<" character is E"<<endl;
                        else
                            cout<<"No."<<lb<<" character is 3"<<endl;
                    }
                    else
                    {
                        if (Mnt_1[lb]<0.5)
                        {
                            if (AsRt[lb]==1)
                                cout<<"No."<<lb<<" character is M"<<endl;
                            else
                                cout<<"No."<<lb<<" character is S"<<endl;
                        }
                        else
                        {
                            if (max_row[lb]<(cord_size[lb][2]/2))
                                cout<<"No."<<lb<<" character is 5"<<endl;
                            else
                                cout<<"No."<<lb<<" character is 2"<<endl;
                        }
                        
                    }
                    
                }
                
                
            }
            else
            {
                if (Symm_y[lb][2]<0.5)
                {
                    if (AsRt[lb]<0.5)
                        cout<<"No."<<lb<<" character is 1"<<endl;
                    else
                        cout<<"No."<<lb<<" character is L"<<endl;
                }
                else
                {
                    if (Mnt_1[lb]<0.7)
                        cout<<"No."<<lb<<" character is T"<<endl;
                    else
                        cout<<"No."<<lb<<" character is I"<<endl;
                }
                
            }
            
        }
        else if (Eulr[lb]==0)
        {
            if (Symm_x[lb][2]<0.85)
            {
                if (Mnt_1[lb]<0.5)
                    cout<<"No."<<lb<<" character is P"<<endl;
                else
                    cout<<"No."<<lb<<" character is 4"<<endl;
            }
            else
            {
                if (Symm_y[lb][2]>0.95)
                    cout<<"No."<<lb<<" character is 0"<<endl;
                else
                {
                    if (Mnt_1[lb]<0.3)
                        cout<<"No."<<lb<<" character is D"<<endl;
                    else
                    {
                        if (min_row[lb]<(cord_size[lb][2]/2))
                            cout<<"No."<<lb<<" character is 6"<<endl;
                        else
                            cout<<"No."<<lb<<" character is 9"<<endl;
                    }
                }
                
            }
            
        }
        else
            cout<<"No."<<lb<<" character is 8"<<endl;
    }
    */
    
    cout<<"The end!"<<endl;
    getchar();
    return 0;
    
}
