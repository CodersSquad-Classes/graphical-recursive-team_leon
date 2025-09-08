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

void savePoints(const vector<Point>& points){
    ofstream file("lines.txt");
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

    

    if (argc != 5) {
        cout << "You must folow one of the following formats: " << endl;
        cout << "--Hilbert <depht> <dx> <dy> : --Hilbert 5 0 2" << endl;
        cout << "--Hilbert <depht> <angle> <lenght> : --Hilbert 5 0 2" << endl;
        return -1;
    }

    string option  = argv[1];

    if (option == "--Hilbert") {
            ofstream output("lines.txt");

        if (!output.is_open()) {
            cerr << "No se pudo abrir el archivo\n";
            return 1;
        }

        streambuf* coutBuf = cout.rdbuf();
        cout.rdbuf(output.rdbuf());

        int depht = stoi(argv[2]);
        int dx = stoi(argv[3]);
        int dy = stoi(argv[4]);
        Point p0 = {0,0};

        Hilbert(depht, dx, dy, p0);

        cout.rdbuf(coutBuf);
        output.close();
        cout << "--Hilbert ran succesfully, check lines.txt" << endl;
    
    } else if(option == "--Koch"){
        int depht = stoi(argv[2]);
        float angle = stoi(argv[3]);
        float lenght = stoi(argv[4]);
        Point p0 = {0.0, 0.0};
        vector<Point> points = Koch(depht, p0, angle, lenght);
        savePoints(points);
        cout << "--Koch ran succesfully, check lines.txt" << endl;

    } else {
        cout << "Please select between <--Hilbert> or <--Koch>";
    }

    return 0;
}