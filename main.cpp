#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <string>
#include <iterator>
#include <fstream>


using namespace std;

void intersection(double a1, double a2, double b1, double b2, double c1, double c2, double &x, double &y)
{
   // находит координаты (x, y), в которых прямые пересекаются
   double det = a1 * b2 - a2 * b1;
   x = (b1 * c2 - b2 * c1) / det;
   y = (a2 * c1 - a1 * c2) / det;
}

int main()
{
   ifstream infile("data.txt");

   string line;
   vector< vector <int> > v1;
   while (getline(infile, line))
   {
      istringstream is(line);
      v1.push_back(
            vector<int>( istream_iterator<int>(is),
                         istream_iterator<int>() ) );
   }
   infile.close();

   cout << "Ломаная: " << endl;
   for (unsigned int p=0; p < v1.size(); p++)
   {
       cout << "x: " << v1[p][0] << " y: " << v1[p][1] << endl;
   }


   double x, y;
   double x1, y1, x2, y2;
   double a1, b1, c1, a2, b2, c2;

   double x3, y3, x4, y4;

   double parts = 0; // количество разбиений

   for (unsigned int first_point_set=0; first_point_set < v1.size()-1; first_point_set++)
   {
      // итерируемся по парам точек, задающих отрезок ломаной
      x1 = v1[first_point_set][0];
      y1 = v1[first_point_set][1];

      x2 = v1[first_point_set+1][0]; 
      y2 = v1[first_point_set+1][1];

      // коэффициенты, задающие уравнение прямой
      a1 = y1 - y2;
      b1 = x2 - x1;
      c1 = x1 * y2 - x2 * y1; 

      for (unsigned int second_point_set=0; second_point_set < v1.size()-1; second_point_set++)
      {
         // итерируемся по другим парам точек
         if (first_point_set != second_point_set)
         {
            x3 = v1[second_point_set][0];
            y3 = v1[second_point_set][1];

            x4 = v1[second_point_set+1][0];
            y4 = v1[second_point_set+1][1];

            // коэффициенты, задающие уравнение второй прямой
            a2 = y3 - y4;
            b2 = x4 - x3;
            c2 = x3 * y4 - x4 * y3;

            intersection(a1, a2, b1, b2, c1, c2, x, y);

            // принадлежит ли пересечение прямой (строгость для неучета точек перегиба ломаной)
            if ((x > x3) and (x < x2))
               parts += 1;
         }
      }
   }
   cout << "Количество разбиений: " << parts + 1;
}
