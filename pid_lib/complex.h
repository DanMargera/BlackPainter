#ifndef COMPLEX_H
#define COMPLEX_H

class Complex
{
public:
    Complex() : r(0), i(0){}
    Complex(double r) : r(r), i(0){}
    Complex(double r, double i) : r(r), i(i) {}

    Complex sum  (Complex c)  { return Complex(r+c.r,i+c.i); }
    Complex sub  (Complex c)  { return Complex(r-c.r,i-c.i); }
    Complex mult (Complex c)  { return Complex(r*c.r-i*c.i,r*c.i+i*c.r); }
    Complex mult (double n)   { return Complex(r*n,i*n); }
    Complex div  (double n)   { return Complex(r/n,i/n); }
    Complex conj ()           { return Complex(r,-i); }
    double  abs  ()           { return sqrt(r*r+i*i); }
    double  phase()           { return atan2(i,r); }

    Complex operator+(Complex c) { return sum(c);  }
    Complex operator-(Complex c) { return sub(c);  }
    Complex operator*(Complex c) { return mult(c); }
    Complex operator*(double c)  { return mult(c); }
    Complex operator/(double c)  { return div(c);  }

    QString toString() {
        QString text;
        text.sprintf("[%+06.2f%+06.2fJ]",r,i);
        return text;
    }

private:
    double r;
    double i;
};

class CVector
{
    friend class CMatrix;
public:
    CVector(int n) : n(n) { c = new Complex[n]; }
    Complex& operator[](int idx){ return c[idx]; }
    int size() { return n; }
    double maxAbs() {
        double max = c[0].abs();
        double aux;
        for(int i = 1; i < n; i++) {
            aux = c[i].abs();
            if(aux>max) max = aux;
        }
        return max;
    }

    double minAbs() {
        double min = c[0].abs();
        double aux;
        for(int i = 1; i < n; i++) {
            aux = c[i].abs();
            if(aux<min) min = aux;
        }
        return min;
    }

    QString toString() {
        QString out = "";
        for(int i = 0; i < n; i++)
            out += c[i].toString() + " ";
        return out;
    }

private:
    CVector(){}
    Complex * c;
    int n;
};

class CMatrix
{
public:
    CMatrix(int x, int y) : x(x), y(y)
    {
        c = new CVector[y];
        for(int i = 0; i < y; i++)
        {
            c[i] = CVector(x);
        }
    }

    CVector& operator[](int idy){ return c[idy]; }
    int width()  { return x; }
    int height() { return y; }

    double maxAbs() {
        double max = c[0].maxAbs();
        double aux;
        for(int i = 1; i < y; i++) {
            aux = c[i].maxAbs();
            if(aux>max) max = aux;
        }
        return max;
    }

    double minAbs() {
        double min = c[0].minAbs();
        double aux;
        for(int i = 1; i < y; i++) {
            aux = c[i].minAbs();
            if(aux<min) min = aux;
        }
        return min;
    }

    QString toString() {
        QString out = "";
        for(int i = 0; i < x; i++)
            out += c[i].toString() + "\n";
        return out;
    }

private:
    CVector * c;
    int x;
    int y;
};

class FFT
{
public:
    static CVector fft1d(CVector in) {
        int N = in.size();
        if (N == 1){
            CVector out(1);
            out[0] = in[0];
            return out;
        } else if (N % 2 != 0) {
            return NULL;
        }

        // Break the array down into two parts and perform FFT of each piece
        CVector part(N / 2);
        for (int k = 0; k < N / 2; k++) {
            part[k] = in[2 * k]; // even terms
        }
        CVector evenfft = fft1d(part);
        for (int k = 0; k < N / 2; k++) {
            part[k] = in[2 * k + 1]; // odd terms
        }
        CVector oddfft = fft1d(part);

        // combine
        CVector out(N);
        for (int k = 0; k < N / 2; k++) {
            double kth = -2 * k * M_PI / N;
            Complex wk(qCos(kth),qSin(kth));
            out[k] = evenfft[k]+(wk*oddfft[k]);
            out[k + N / 2] = evenfft[k]-(wk*oddfft[k]);
        }
        return out;
    }

    static CVector ifft1d(CVector in) {
        int N = in.size();

        CVector out(N);
        for (int i = 0; i < N; i++)
        {
            out[i] = in[i].conj();
        }

        out = fft1d(out);
        for (int i = 0; i < N; i++)
        {
            out[i] = out[i].conj()/N;
        }

        return out;
    }

    static CMatrix fft2d(CMatrix in)
    {
        int nrows = in.height();
        int ncols = in.width();

        CMatrix rowwise(ncols,nrows);
        for (int i=0; i < ncols; ++i){
            rowwise[i] = fft1d(in[i]);
        }

        CMatrix result(ncols,nrows);
        {
            CVector tmp(ncols);
            for (int j=0; j < nrows; ++j){
                for (int i=0; i < ncols; ++i){
                    tmp[i] = rowwise[i][j];
                }
                CVector tmp2 = fft1d(tmp);
                for (int i=0; i < ncols; ++i){
                    result[i][j] = tmp2[i];
                }
            }
        }
        return result;
    }

    static CMatrix ifft2d(CMatrix in)
    {
        int nrows = in.height();
        int ncols = in.width();

        CMatrix rowwise(ncols,nrows);
        for (int i=0; i < ncols; ++i){
            rowwise[i] = ifft1d(in[i]);
        }

        CMatrix result(ncols,nrows);
        {
            CVector tmp(ncols);
            for (int j=0; j < nrows; ++j){
                for (int i=0; i < ncols; ++i){
                    tmp[i] = rowwise[i][j];
                }
                CVector tmp2 = ifft1d(tmp);
                for (int i=0; i < ncols; ++i){
                    result[i][j] = tmp2[i];
                }
            }
        }
        return result;
    }
};

#endif // COMPLEX_H
