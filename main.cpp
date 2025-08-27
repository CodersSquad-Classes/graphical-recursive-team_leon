#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

#define M_PI 3.14159265358979323846
#define degToRad(angleInDegrees) ((angleInDegrees) * M_PI / 180.0f)

using namespace std;

struct Point {
	float x, y;
    Point() : x(0), y(0) {}
	Point(float x, float y) : x(x), y(y) {}
};

vector<Point> Koch(int depth, Point p1, float angle, float length){

    vector<Point> points; 

    if (depth == 0) {
        points.push_back(p1);
        points.push_back(Point(
            p1.x + length * cos(degToRad(angle)),
            p1.y + length * sin(degToRad(angle))
        ));
        return points;
    }

    Point p2(
        p1.x + length / 3.0f * cos(degToRad(angle)),
        p1.y + length / 3.0f * sin(degToRad(angle)));
    Point p4(
        p1.x + (2/3.0f) * length * cos(degToRad(angle)),
        p1.y + (2/3.0f) * length * sin(degToRad(angle)));

    Point p3(
        p2.x + (length/3.0f) * cos(degToRad(angle + 60)),
        p2.y + (length / 3.0f) * sin(degToRad(angle + 60)));

    
    vector<Point> left = Koch(depth - 1, p1, angle, length / 3.0f);
    vector<Point> top = Koch(depth - 1, p2, angle + 60, length / 3.0f);
    vector<Point> right = Koch(depth - 1, p3, angle - 60, length / 3.0f);
    vector<Point> bottom = Koch(depth - 1, p4, angle, length / 3.0f);
    
    points.insert(points.end(), left.begin(), left.end() - 1);
    points.insert(points.end(), top.begin(), top.end() - 1);
    points.insert(points.end(), right.begin(), right.end() - 1);
    points.insert(points.end(), bottom.begin(), bottom.end());

    return points;
}

void savePoints(const vector<Point>& points, const char* filename){
    ofstream file(filename);
    if(!file.is_open()){
        cerr << "No se pudo abrir el archivo\n";
        return;
    }
    for(size_t i = 0; i < points.size() - 1; i++){
        file << "(" << (int)points[i].x << "," << (int)points[i].y << ")";
        file << "(" << (int)points[i + 1].x << "," << (int)points[i + 1].y << ")\n";
    }

    file.close();

}

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

    vector<Point> points = Koch(5, p0, 0, 100);
    savePoints(points, "koch_fractal.txt");

    return 0;
}