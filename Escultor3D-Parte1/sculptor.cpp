#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cmath>
#include <string>
#include <math.h>

using namespace std;

#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    v = new Voxel**[nx];
        for(int i=0; i<nx; i++){
            v[i] = new Voxel*[ny];
                for(int j=0; j<ny; j++){
                    v[i][j] = new Voxel[nz];
                }
        }

    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
                v[i][j][k].isOn = false;
            }
        }
    }
}
Sculptor::~Sculptor()
{
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            delete[] v[i][j];
        }
    }
    for (int i = 0; i < nx; i++) {
        delete[] v[i];
    }
    delete[] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha){
    this->r = r; //Cor vermelha.
    this->g = g; //Cor verde.
    this->b = b; //Cor azul.
    this->a = alpha; //Opacidade.
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    int i,j,k;
    for(i=x0;i<x1;i++){
        for(j=y0;j<y1;j++){
            for(k=z0;k<z1;k++){
                cutVoxel(i,j,k);
               
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){

        double rd=radius/2.0;
        //Variáveis que representam a distânica do centro da esfera para o Voxel.
        double dist;
        for(int i=0;i<nx;i++){
            for(int j=0;j<ny;j++){
                for(int k=0;k<nz;k++){
                    //Equação da esfera.
                    dist = (i-xcenter/2.0) * (i-xcenter/2.0 ) / (rd*rd) +
                           (j-ycenter/2.0) * (j-ycenter/2.0) / (rd*rd) +
                           (k-zcenter/2.0) * (k-zcenter/2.0 ) / (rd*rd);
                   //Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a presença de um Voxel no local.
                    if(dist<=1.0){
                        v[i][j][k].isOn=true;
                        v[i][j][k].r=r;
                        v[i][j][k].b=b;
                        v[i][j][k].g=g;
                        v[i][j][k].a=a;
                    }
                }
            }
        }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    //Seguindo a mesma lógica do putSphere, porém agora ao invés de chamar putVoxel será chamado a função cutVoxel, para retirar um voxel.

    double rd=radius/2.0;
    double dist;
    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                dist = (i-xcenter/2.0) * (i-xcenter/2.0) / (rd*rd) +
                       (j-ycenter/2.0) * (j-ycenter/2.0) / (rd*rd) +
                       (k-zcenter/2.0) * (k-zcenter/2.0) / (rd*rd);   
                if(dist<=1.0){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

        //Variaveis para armazenarem os raios, assim, efetuando a transformação de int para double.
        double _rx=rx/2.0,_ry=ry/2.0,_rz=rz/2.0;
        // Variáveis que representam a distânica do centro do elipsóide para o Voxel.
        double dist;
        for(int i=0;i<nx;i++){
            for(int j=0;j<ny;j++){
                for(int k=0;k<nz;k++){
                    //Equação do elipsóide.
                    dist = (i-xcenter/2.0) * (i-xcenter/2.0) / (_rx*_rx) +
                           (j-ycenter/2.0) * (j-ycenter/2.0) / (_ry*_ry) +
                           (k-zcenter/2.0) * (k-zcenter/2.0) / (_rz*_rz);
                    // Caso as condições sejam verdadeira, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a presença de um Voxel no local.
                    if((dist<=1)&&(i<nx&&i>=0)&&(j<ny&&j>=0)&&(k<nz&&k>=0)){
                        v[i][j][k].isOn=true;
                        v[i][j][k].r=r;
                        v[i][j][k].b=b;
                        v[i][j][k].g=g;
                        v[i][j][k].a=a;
                    }
                }
            }
        }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){

    //Variáveis para armazenarem os raios, assim, efetuando a transformação de int para double.
    double _rx=rx/2.0,_ry=ry/2.0,_rz=rz/2.0;
    //Variáveis que representam a distânica do centro do elipsóide para o Voxel.
    double dist;
    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                //Equação do elipsóide.
                dist = (i-xcenter/2.0) * (i-xcenter/2.0) / (_rx*_rx) +
                       (j-ycenter/2.0) * (j-ycenter/2.0) / (_ry*_ry) +
                       (k-zcenter/2.0) * (k-zcenter/2.0) / (_rz*_rz);
                //Caso as condições sejam verdadeira, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a presença de um Voxel no local.
                if((dist<=1)&&(i<nx&&i>=0)&&(j<ny&&j>=0)&&(k<nz&&k>=0)){
                    v[i][j][k].isOn=false;
                }
            }
        }
    }
}
// crinando um arquivo .off
void Sculptor::writeOFF(char *filename){
    int NVoxels = 0, NVertices, NFaces;
    float faces = 0;

    ofstream fout;

    fout.open(filename);
    if (!fout.is_open()){
       exit(1);
       cout << "Não foi possivel gravar no arquivo";
    }

    fout << "OFF \n";

    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            for(int k=0;k<nz;k++){
                if (v[i][j][k].isOn == true){
                    NVoxels++;
                }
            }
        }
    }

    NVertices = 8*NVoxels;
    NFaces = 6*NVoxels;

    fout << NVertices << " " << NFaces << " " << 0 << endl;

    //Vertices do cubo sendo inseridos no aqruivo OFF
    for(int i=0; i<nz; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nx; k++){
                if(v[i][j][k].isOn){
                    fout << i-0.5 << " " << j+0.5 << " " << k-0.5 << endl
                         << i-0.5 << " " << j-0.5 << " " << k-0.5 << endl
                         << i+0.5 << " " << j-0.5 << " " << k-0.5 << endl
                         << i+0.5 << " " << j+0.5 << " " << k-0.5 << endl
                         << i-0.5 << " " << j+0.5 << " " << k+0.5 << endl
                         << i-0.5 << " " << j-0.5 << " " << k+0.5 << endl
                         << i+0.5 << " " << j-0.5 << " " << k+0.5 << endl
                         << i+0.5 << " " << j+0.5 << " " << k+0.5 << endl;
                 }
            }
        }
    }
    //Faces do cubo sendo inseridos no arquivo OFF
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(v[i][j][k].isOn){
                    fout << 4 << " " << 0+faces << " " << 3+faces << " " << 2+faces << " " << 1+faces << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl
                         << 4 << " " << 4+faces << " " << 5+faces << " " << 6+faces << " " << 7+faces<< " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl
                         << 4 << " " << 0+faces << " " << 1+faces << " " << 5+faces << " " << 4+faces << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl
                         << 4 << " " << 0+faces << " " << 4+faces << " " << 7+faces << " " << 3+faces << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl
                         << 4 << " " << 3+faces << " " << 7+faces << " " << 6+faces << " " << 2+faces << " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl
                         << 4 << " " << 1+faces << " " << 2+faces << " " << 6+faces << " " << 5+faces<< " "
                         << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                    faces = faces+8;

                 }
            }
        }
    }

    fout.close();
}



