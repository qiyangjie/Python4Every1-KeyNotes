#pragma once
class CRectangle
{
public:
	int w, h;
	
	void Init(int w_, int h_) {
		w = w_;
		h = h_;
	}

	int Area() {
		return w * h;
	}

	int Perimeter() {
		return 2 * (w + h);
	}
};