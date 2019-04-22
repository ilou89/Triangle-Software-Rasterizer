#include "baseBresenham.h"

const Color RED   = Color(255, 0, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color BLUE  = Color(0, 0, 255, 255);
const Color WHITE = Color(255, 255, 255, 255);

BaseBresenham::BaseBresenham(Bitmap& bmp, ModelLoader& model)
 : bmp(bmp), model(model)
{

}

BaseBresenham::~BaseBresenham()
{

}

void
BaseBresenham::line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, const Color& color)
{
    int xDirection = 1;
    int dx, dy;

    if(y0 > y1) {
        std::swap(y0, y1);
        std::swap(x0, x1);
    }

    dx = x1 - x0;
    dy = y1 - y0;

    if(dx < 0) {
        dx = -dx;
        xDirection = -xDirection;
    }

    //vertical line
    if(dx == 0) {
        vertical(x0, y0, dy, color);
        return;
    }

    //horizontal line
    if(dy == 0){
        horizontal(x0, y0, dx, xDirection, color);
        return;
    }

    //diagonal line
    if(dx == dy){
        diagonal(x0, y0, dx, xDirection, color);
        return;
    }

    if(dx > dy) {
        octant03(x0, y0, dx, dy, xDirection, color);
    } else {
        octant12(x0, y0, dx, dy, xDirection, color);
    }
}

void
BaseBresenham::drawLines()
{
    //y increasing octants 0-3
    line(13, 20, 500, 400, WHITE);
    bmp.setPixel(13, 20, RED);
    bmp.setPixel(500, 400, RED);
    line(20, 13, 400, 500, GREEN);
    bmp.setPixel(20, 13, RED);
    bmp.setPixel(400, 500, RED);
    line(400, 130, 200, 550, WHITE);
    bmp.setPixel(400, 130, RED);
    bmp.setPixel(200, 550, RED);
    line(790, 200, 130, 400, GREEN);
    bmp.setPixel(790, 200, RED);
    bmp.setPixel(130, 400, RED);

    //y increasing octants 4-7
    line(700, 500, 10, 10, BLUE);
    bmp.setPixel(700, 500, RED);
    bmp.setPixel(10, 10, RED);
    line(500, 550, 10, 13, WHITE);
    bmp.setPixel(500, 550, RED);
    bmp.setPixel(10, 13, RED);
    line(200, 50, 350, 450, BLUE);
    bmp.setPixel(200, 50, RED);
    bmp.setPixel(350, 450, RED);
    line(50, 590, 790, 100, GREEN);
    bmp.setPixel(50, 590, RED);
    bmp.setPixel(790, 100, RED);

    //vertical
    line(600, 100, 600, 500, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(600, 500, WHITE);
    line(200, 500, 200, 100, RED);
    bmp.setPixel(200, 500, WHITE);
    bmp.setPixel(200, 100, WHITE);

    //horizontal
    line(200, 500, 600, 500, RED);
    bmp.setPixel(200, 500, WHITE);
    bmp.setPixel(600, 500, WHITE);
    line(600, 100, 200, 100, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(200, 100, WHITE);

    //diagonal
    line(200, 100, 600, 500, RED);
    bmp.setPixel(200, 100, WHITE);
    bmp.setPixel(600, 500, WHITE);
    line(600, 100, 200, 500, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(200, 500, WHITE);
}

void
BaseBresenham::vertical(unsigned int x0, unsigned int y0, int dy, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dy--) {
        y0++;
        bmp.setPixel(x0, y0, color);
    }
}

void
BaseBresenham::horizontal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dx--) {
        x0 += xDirection;
        bmp.setPixel(x0, y0, color);
    }
}

void
BaseBresenham::diagonal(unsigned int x0, unsigned int y0, int dx, int xDirection, const Color& color)
{
    bmp.setPixel(x0, y0, color);
    while(dx--) {
        x0 += xDirection;
        y0++;
        bmp.setPixel(x0, y0, color);
    }
}

bool
BaseBresenham::wireframe(bool xmlSVG)
{
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();

	std::ofstream file;
	if (xmlSVG) {
		file.open("./lines.svg");
		if (!file.is_open()) {
			return false;
		}
		file << "<svg version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns=\"http://www.w3.org/2000/svg\" height=\""
             << height << "\" width=\"" << width << "\">" << std::endl;
	}

    for (int i = 0; i < model.indicesSize(); ++i) {
        std::vector<int> face = model.getIndicesAt(i);
        for (int j = 0; j < 3; ++j) {

            /**
             * Assume that the vertices read from .obj file
             * are already projected and are in screen space,
             * otherwise perspective division would be needed
             */
            Vec3f v0 = model.getVerticesAt(face[j]);
            Vec3f v1 = model.getVerticesAt(face[(j + 1) % 3]);

            /**
             * Normalize coordinates (from [-1,1] -> [0,1])
             * Normalized Device Coordinates
             */
            float x0_proj_remap = (v0.x + 1.0f) / 2;
            float y0_proj_remap = (v0.y + 1.0f) / 2;
            float x1_proj_remap = (v1.x + 1.0f) / 2;
            float y1_proj_remap = (v1.y + 1.0f) / 2;

            /**
             * Express normalized coordinates in terms of pixels
             * Raster Space
             */
            int x0_proj_pix  = static_cast<int>(x0_proj_remap * width);
            int y0_proj_pix  = static_cast<int>(y0_proj_remap * height);
            int x1_proj_pix  = static_cast<int>(x1_proj_remap * width);
            int y1_proj_pix  = static_cast<int>(y1_proj_remap * height);

            line(x0_proj_pix, y0_proj_pix, x1_proj_pix, y1_proj_pix, WHITE);

			if (xmlSVG) {
            	file << "<line x1=\"" << x0_proj_pix << "\" y1=\""
                     << height - y0_proj_pix << "\" x2=\"" << x1_proj_pix
                     << "\" y2=\"" << height - y1_proj_pix
                     << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\" />\n";
			}
        }
    }

	if (xmlSVG) {
		file << "</svg>\n";
		file.close();
	}

	return true;
}

