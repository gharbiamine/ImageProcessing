#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

// enum Format
// {
//     P2,
//     P3,
//     P5,
//     P6
// };

class Image
{
public:
    string format;
    string commentaire;
    int nbCol;
    int nbLig;
    unsigned char valMax;
};

class PPM : public Image
{
public:
    vector<vector<unsigned char>> G;
    vector<vector<unsigned char>> B;
    vector<vector<unsigned char>> R;
};
class PGM : public Image
{
public:
    vector<vector<unsigned char>> mat;
    vector<vector<unsigned char>> lire(string nom)
    {

        ifstream input(nom);
        string buffer;
        string line;
        int lx, ly;
        getline(input, this->format);
        getline(input, this->commentaire);
        getline(input, buffer);
        string x, y;
        bool first = true;
        for (char c : buffer)
        {
            if (c == ' ')
            {
                first = false;
                continue;
            }
            if (first)
            {
                x += c;
            }
            else
            {
                y += c;
            }
        }
        lx = stoi(x);
        ly = stoi(y);
        this->nbLig = lx;
        this->nbCol = ly;
        getline(input, buffer);
        this->valMax = stoi(buffer);
        for (int i = 0; i < lx; i++)
        {
            vector<unsigned char> line;
            for (int j = 0; j < ly; j++)
            {
                getline(input, buffer, ' ');
                if (!buffer.empty())
                {
                    unsigned char c = (unsigned char)stoi(buffer);
                    line.push_back(c);
                }
            }
            mat.push_back(line);
        }
        return mat;
    }
    void ecrire(string nom)
    {
        ofstream outfile;
        outfile.open(nom);
        outfile << this->format << endl;
        outfile << this->commentaire << endl;
        string temp = to_string(this->nbLig) + " " + to_string(this->nbCol);
        outfile << temp << endl;
        outfile << to_string(valMax) << endl;
        for (int i = 0; i < this->nbLig; i++)
        {
            for (int j = 0; j < this->nbCol; j++)
            {
                outfile << to_string(this->mat[i][j]) + " ";
                
            }
        }
        outfile.close();
    }
    double moyenneGris()
    {
        int sum = 0;
        for (int i = 0; i < this->nbLig; i++)
        {
            for (int j = 0; j < this->nbCol; j++)
            {
                sum += stoi(to_string(this->mat[i][j]));
            }
        }
        return (double)sum / (this->nbLig * this->nbCol);
    }

    double ecartType()
    {
        double moy = this->moyenneGris();
        int sum = 0;
        for (int i = 0; i < this->nbLig; i++)
        {
            for (int j = 0; j < this->nbCol; j++)
            {
                sum += (stoi(to_string(this->mat[i][j])) - moy) * (stoi(to_string(this->mat[i][j])) - moy);
            }
        }
        return sqrt((double)sum / (this->nbLig * this->nbCol));
    }
    vector<unsigned char> hist()
    {
        vector<unsigned char> histogram(this->valMax, 0);
        {
            for (int i = 0; i < this->nbLig; i++)
            {
                for (int j = 0; j < this->nbCol; j++)
                {

                    histogram[(int)(mat[i][j])] += 1;
                }
            }
        }
        return histogram;
    }
    vector<int> histCum(vector<unsigned char> hist)
    {
        vector<int> histC;
        histC.push_back(hist[0]);
        for (int i = 1; i < hist.size() - 1; i++)
        {
            histC.push_back((hist[i] + histC[i - 1]));
        }
        return histC;
    }
};

int main()
{
    PGM pgm1, pgm2;
    // pgm1.format = "P2";
    // pgm1.commentaire = "abc";
    // pgm1.nbCol = 2;
    // pgm1.nbLig = 2;
    // pgm1.valMax = 255;
    // vector<unsigned char> l1 = {146, 49};
    // vector<unsigned char> l2 = {146, 49};
    // pgm1.mat.push_back(l1);
    // pgm1.mat.push_back(l2);
    // pgm1.ecrire("test.txt", pgm1);
    pgm2.mat = pgm2.lire("chat.pgm");
    pgm2.ecrire("test1.txt");
    cout << "moyenne pgm2 = " << pgm2.moyenneGris() << endl;
    cout << "ecart Type pgm2 = " << pgm2.ecartType() << endl;
    cout << "affichage histogramme  : " << endl;
    vector<unsigned char> hist = pgm2.hist();
    for (unsigned char c : hist)
    {
        cout << (int)c << endl;
    }
    cout << "affichage histogramme cumule : " << endl;
    vector<int> hist1 = pgm2.histCum(hist);
    for (int c : hist1)
    {
        cout << c << endl;
    }
    return 0;
}