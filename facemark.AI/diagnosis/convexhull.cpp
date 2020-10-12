#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long int T;
#define vp vector<POINT>
#define EPS 1e-8
struct POINT {
	T x, y, dis;
	double angle;
	POINT() {};
	POINT(T _x, T _y) :x(_x), y(_y) {};
	bool operator()(POINT A, POINT B){
		if (A.y!=B.y) return A.y < B.y;
		return A.x<B.x;
	}
	bool operator<(const POINT &jcu) {
		if (-EPS < angle - jcu.angle && angle - jcu.angle < EPS) return dis < jcu.dis;
		return angle < jcu.angle;
	}
};
struct ConvexHull {
private:
	vp a, output;
	int n;

	int ccw(POINT a, POINT b, POINT c) {
		T t = (b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x);
		if (t > EPS) return 1;
		if (t < EPS) return -1;
		return 0;
	}
	
	void calc() {
		sort(a.begin(), a.end(), POINT());
		a[0].angle = -10000;
		for (int i = 1; i < n; i++) {
			a[i].angle = atan2(a[i].y - a[0].y, a[i].x - a[0].x);
			a[i].dis = (a[i].y - a[0].y)*(a[i].y - a[0].y) + (a[i].x - a[0].x)*(a[i].x - a[0].x);
		}
		sort(a.begin(), a.end());

		vp stack;
		stack.push_back(a[0]);
		stack.push_back(a[1]);
		for (int i = 2; i < n; i++) {
			while (stack.size() > 1) {
				int m = stack.size();
				int t = ccw(stack[m - 2], stack[m - 1], a[i]);
				if (t <= 0) stack.pop_back();
				else break;
			}
			stack.push_back(a[i]);
		}
		output = stack;
	}

public:
	ConvexHull() {};
	ConvexHull(vp _input) {
		a.clear(); output.clear();
		a = _input;
		n = a.size();
		calc();
	}
	vp result() {
		return output;
	}
};