#include "renderer.h"

const Color RED   = Color(255, 0, 0, 255);
const Color GREEN = Color(0, 255, 0, 255);
const Color BLUE  = Color(0, 0, 255, 255);
const Color WHITE = Color(255, 255, 255, 255);

Renderer::Renderer(int choice, Bitmap &bitmap, ModelLoader &model)
 : bmp(bitmap), model(model)
{
    lineDrawer = LineDrawerFactory::makeLineDrawer(choice, bitmap);
}

Renderer::~Renderer()
{

}

void
Renderer::triangle()
{
    lineDrawer->line(10, 70, 50, 160, RED);
    lineDrawer->line(50, 160, 70, 80, RED);
    lineDrawer->line(70, 80, 10, 70, RED);
}

void
Renderer::drawLines()
{
    //y increasing octants 0-3
    lineDrawer->line(13, 20, 500, 400, WHITE);
    bmp.setPixel(13, 20, RED);
    bmp.setPixel(500, 400, RED);
    lineDrawer->line(20, 13, 400, 500, GREEN);
    bmp.setPixel(20, 13, RED);
    bmp.setPixel(400, 500, RED);
    lineDrawer->line(400, 130, 200, 550, WHITE);
    bmp.setPixel(400, 130, RED);
    bmp.setPixel(200, 550, RED);
    lineDrawer->line(790, 200, 130, 400, GREEN);
    bmp.setPixel(790, 200, RED);
    bmp.setPixel(130, 400, RED);

    //y increasing octants 4-7
    lineDrawer->line(700, 500, 10, 10, BLUE);
    bmp.setPixel(700, 500, RED);
    bmp.setPixel(10, 10, RED);
    lineDrawer->line(500, 550, 10, 13, WHITE);
    bmp.setPixel(500, 550, RED);
    bmp.setPixel(10, 13, RED);
    lineDrawer->line(200, 50, 350, 450, BLUE);
    bmp.setPixel(200, 50, RED);
    bmp.setPixel(350, 450, RED);
    lineDrawer->line(50, 590, 790, 100, GREEN);
    bmp.setPixel(50, 590, RED);
    bmp.setPixel(790, 100, RED);

    //vertical
    lineDrawer->line(600, 100, 600, 500, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(600, 500, WHITE);
    lineDrawer->line(200, 500, 200, 100, RED);
    bmp.setPixel(200, 500, WHITE);
    bmp.setPixel(200, 100, WHITE);

    //horizontal
    lineDrawer->line(200, 500, 600, 500, RED);
    bmp.setPixel(200, 500, WHITE);
    bmp.setPixel(600, 500, WHITE);
    lineDrawer->line(600, 100, 200, 100, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(200, 100, WHITE);

    //diagonal
    lineDrawer->line(200, 100, 600, 500, RED);
    bmp.setPixel(200, 100, WHITE);
    bmp.setPixel(600, 500, WHITE);
    lineDrawer->line(600, 100, 200, 500, RED);
    bmp.setPixel(600, 100, WHITE);
    bmp.setPixel(200, 500, WHITE);
}

bool
Renderer::wireframe(bool xmlSVG)
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

            if (x0_proj_pix >= static_cast<int>(width)) {
                x0_proj_pix = static_cast<int>(width - 1);
            }
            if (x1_proj_pix >= static_cast<int>(width)) {
                x1_proj_pix = static_cast<int>(width - 1);
            }
            if (y0_proj_pix >= static_cast<int>(height)) {
                y0_proj_pix = static_cast<int>(height - 1);
            }
            if (y1_proj_pix >= static_cast<int>(height)) {
                y1_proj_pix = static_cast<int>(height - 1);
            }

            lineDrawer->line(x0_proj_pix, y0_proj_pix, x1_proj_pix, y1_proj_pix, WHITE);

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

