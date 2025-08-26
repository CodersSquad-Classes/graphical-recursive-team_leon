#include <iostream>
#include <fstream>
using namespace std;


struct Point{
    int x, y;
};

void DrawRelative(const int& dx, const int& dy, Point& p){
    cout << "(" << p.x  << "," << p.y << ")";
    p.x += dx; 
    p.y += dy;
    cout << "(" << p.x  << "," << p.y << ")\n";
}

void Hilbert(int depht, const int& dx, const int& dy, Point& p){
    if(depht < 0)
        return;
    
    Hilbert(depht-1, dy, dx, p);
    DrawRelative(dx, dy, p);

    Hilbert(depht-1, dx, dy, p);
    DrawRelative(dy, dx, p);

    Hilbert(depht-1, dx, dy, p);
    DrawRelative(-dx, -dy, p);

    Hilbert(depht-1, -dy, -dx, p);

}

int main(int argc, char** argv){

    int depht, dx, dy;

    if (argc < 4) {
        cout << "You must pass a a float number and the digit to find" << endl;
        cout << "Example: " << " 5 10 0" << endl;
        return -1;
    }

    ofstream output("output.txt");

    if (!output.is_open()) {
        cerr << "No se pudo abrir el archivo\n";
        return 1;
    }

    streambuf* coutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());
    
    
    depht = stoi(argv[1]);
    dx = stoi(argv[2]);
    dy = stoi(argv[3]);
    
    Point p0 = {0,0};
    Hilbert(depht, dx, dy, p0);

    cout.rdbuf(coutBuf);
    output.close();
    return 0;
}