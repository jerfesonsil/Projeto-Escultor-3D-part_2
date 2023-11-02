#include "Sculptor.h"

// CONSTRUTOR
Sculptor::Sculptor(int _nx, int _ny, int _nz) : v(nullptr), nx(_nx), ny(_ny), nz(_nz), r(0), g(0), b(0), a(0){

  // Alocação dinâmica
  v = new Voxel **[nx];
  for (int i = 0; i < nx; i++){
    v[i] = new Voxel *[ny];
    for (int j = 0; j < ny; j++){
      v[i][j] = new Voxel[nz];
      for (int k = 0; k < nz; k++){
         v[i][j][k].show =  false;
         v[i][j][k].a = 0;
         v[i][j][k].r = 0;
         v[i][j][k].g = 0;
         v[i][j][k].b = 0;
      }
    }
  }
}

// DESTRUTOR
Sculptor ::~Sculptor(){

  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      delete[] v[i][j];
    }
    delete[] v[i];
  }
  delete[] v;
}

// Define a cor atual do desenho
void Sculptor ::setColor(float _r, float _g, float _b, float _a){
  r = _r;
  g = _g;
  b = _b;
  a = _a;
}

// Ativa o voxel na posição (x,y,z) (fazendo show = true) e atribui ao mesmo a cor atual de desenho
void Sculptor ::putVoxel(int x, int y, int z){
  v[x][y][z].show = true;
  v[x][y][z].r = r;
  v[x][y][z].g = g;
  v[x][y][z].b = b;
  v[x][y][z].a = a;
}

// Desativa o voxel na posição (x,y,z) (fazendo show = false)
void Sculptor ::cutVoxel(int x, int y, int z){
  v[x][y][z].show = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
  // Ativar Voxels dentro das coordenadas do cubo
  for (int i = x0; i <= x1; i++){
    for (int j = y0; j <= y1; j++){
      for (int k = z0; k <= z1; k++){
        putVoxel(i, j, k);
      }
    }
  }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
  // Desativar Voxels dentro das coordenadas do cubo
  for (int i = x0; i <= x1; i++){
    for (int j = y0; j <= y1; j++){
      for (int k = z0; k <= z1; k++){
        cutVoxel(i, j, k);
      }
    }
  }
}

// Cria uma esfera
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        float dx = i - xcenter;
        float dy = j - ycenter;
        float dz = k - zcenter;
        float distance = sqrt(dx * dx + dy * dy + dz * dz);
        if (distance <= radius){
          putVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
  // Desativar Voxels dentro de uma esfera com centro e raio especificados
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if ((i - xcenter) * (i - xcenter) + (j - ycenter) * (j - ycenter) +
                (k - zcenter) * (k - zcenter) <=
            radius * radius){
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz){
  // Ativa Voxels que satisfazem a equação do elipsóide
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        float normalizedX = static_cast<float>(i - xcenter) / rx;
        float normalizedY = static_cast<float>(j - ycenter) / ry;
        float normalizedZ = static_cast<float>(k - zcenter) / rz;
        float distance = normalizedX * normalizedX + normalizedY * normalizedY +
                         normalizedZ * normalizedZ;

        if (distance <= 1.0){
          putVoxel(i, j, k);
        }
      }
    }
  }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx,
                            int ry, int rz){
  // Desativa Voxels que satisfazem a equação do elipsóide
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        float normalizedX = static_cast<float>(i - xcenter) / rx;
        float normalizedY = static_cast<float>(j - ycenter) / ry;
        float normalizedZ = static_cast<float>(k - zcenter) / rz;
        float distance = normalizedX * normalizedX + normalizedY * normalizedY +
                         normalizedZ * normalizedZ;

        if (distance <= 1.0){
          cutVoxel(i, j, k);
        }
      }
    }
  }
}

// Função que cria o arquivo .off
void Sculptor::writeOFF(char const *filename){
  std::ofstream outfile(filename);
  // Se o arquivo não for gerado gera um aviso
  if (!outfile.is_open()){
    std::cerr << "Erro ao abrir o arquivo para escrita." << std::endl;
    return;
  }

  // Escreva os dados da escultura no formato OFF
  int numVertices = 0;
  int numFaces = 0;

  // Calcula o número de Voxels ativos (show == true)
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show) {
          numVertices += 8;
          numFaces += 6;
        }
      }
    }
  }

  // Escreve primeiro a palavra OFF no arquivo
  outfile << "OFF" << std::endl;
  // Esvreve o número de vértices, faces, e arestas (0)
  outfile << numVertices << " " << numFaces << " 0" << std::endl;

  // Escreve as coordenadas dos vértices
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){
          outfile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
          outfile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
          outfile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
          outfile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
        }
      }
    }
  }

  // Escreve os índices das faces
  int offset = 0;
  for (int i = 0; i < nx; i++){
    for (int j = 0; j < ny; j++){
      for (int k = 0; k < nz; k++){
        if (v[i][j][k].show){
          outfile << std::fixed
                  << std::setprecision(2); // Usa std::fixed e std::setprecision
          outfile << "4 " << 0 + offset << " " << 3 + offset << " "
                  << 2 + offset << " " << 1 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 4 + offset << " " << 5 + offset << " "
                  << 6 + offset << " " << 7 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 0 + offset << " " << 1 + offset << " "
                  << 5 + offset << " " << 4 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 0 + offset << " " << 4 + offset << " "
                  << 7 + offset << " " << 3 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 1 + offset << " " << 2 + offset << " "
                  << 6 + offset << " " << 5 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          outfile << "4 " << 2 + offset << " " << 3 + offset << " "
                  << 7 + offset << " " << 6 + offset << " " << v[i][j][k].r
                  << " " << v[i][j][k].g << " " << v[i][j][k].b << " "
                  << v[i][j][k].a << std::endl;
          offset += 8;
        }
      }
    }
  }

  // Feche a seção OFF
  outfile.close();

  // Mensagem no terminal que informa que o arquivo .off foi criado
  std ::cout << "Arquivo " << filename << " criado" << std::endl;
}
