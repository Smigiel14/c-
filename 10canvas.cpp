#include <vector>
#include <iostream>

class Canvas {
public:
    Canvas(size_t w, size_t h) : width(w), height(h), grid(h, std::vector<bool>(w, false)) {}
    
    void set(size_t x, size_t y) {
        if (x < width && y < height)
            grid[y][x] = true;
    }

    void print() const {
        for (const auto& row : grid) {
            for (bool c : row) {
                std::cout << (c ? "\xE2\x96\x88" : " ");
            }
            std::cout << std::endl;
        }
    }

    size_t getWidth() const {
        return width; 
    }
    size_t getHeight() const {
        return height; 
    }

private:
    std::vector<std::vector<bool>> grid;
    size_t width, height;
};

class Painter {
protected:
    Canvas& canvas;
public:
    Painter(Canvas& c) : canvas(c) {}
    virtual void paint() = 0;
};

class VerticalLinePainter : public Painter {
    size_t x;
public:
    VerticalLinePainter(Canvas& c, size_t x) : Painter(c), x(x) {}

    void paint() override {
        for (size_t y = 0; y < canvas.getHeight(); ++y)
            canvas.set(x, y);
    }
};

class HorizontalLinePainter : public Painter {
    size_t y;
public:
    HorizontalLinePainter(Canvas& c, size_t y) : Painter(c), y(y) {}

    void paint() override {
        for (size_t x = 0; x < canvas.getWidth(); ++x)
            canvas.set(x, y);
    }
};

class RectanglePainter : public Painter {
public:
    RectanglePainter(Canvas& c) : Painter(c) {}

    void paint() override {
        size_t w = canvas.getWidth();
        size_t h = canvas.getHeight();

        for (size_t x = 0; x < w; ++x) {
            canvas.set(x, 0);
            canvas.set(x, h - 1);
        }
        
        for (size_t y = 0; y < h; ++y) {
            canvas.set(0, y);
            canvas.set(w - 1, y);
        }
    }
};

int main() {
    std::cout << "Linia pionowa x=5 " << std::endl;
    Canvas c1(20, 10);
    VerticalLinePainter vlp(c1, 5);
    vlp.paint();
    c1.print();

    std::cout << " Linia pozioma y=3" << std::endl;
    Canvas c2(20, 10);
    HorizontalLinePainter hlp(c2, 3);
    hlp.paint();
    c2.print();

    std::cout << "Prostokąt " << std::endl;
    Canvas c3(20, 10);
    RectanglePainter rp(c3);
    rp.paint();
    c3.print();
    
    return 0;
}