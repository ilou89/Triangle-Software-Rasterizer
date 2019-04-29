#include "renderer.h"

const Color RED    = Color(255, 0, 0, 255);
const Color GREEN  = Color(0, 255, 0, 255);
const Color BLUE   = Color(0, 0, 255, 255);
const Color WHITE  = Color(255, 255, 255, 255);
const Color PURPLE = Color(128, 0, 128, 255);

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
    Point2D p0(10, 70);
    Point2D p1(50, 160);
    Point2D p2(70, 80);

    lineDrawer->line(p0, p1, RED);
    lineDrawer->line(p1, p2, RED);
    lineDrawer->line(p2, p0, RED);
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
            Point2D p0_proj;
            p0_proj.x  = static_cast<unsigned int>(x0_proj_remap * width);
            p0_proj.y = static_cast<unsigned int>(y0_proj_remap * height);
            Point2D p1_proj;
            p1_proj.x = static_cast<unsigned int>(x1_proj_remap * width);
            p1_proj.y = static_cast<unsigned int>(y1_proj_remap * height);

            if (p0_proj.x >= width) {
                p0_proj.x = width - 1;
            }
            if (p1_proj.x >= width) {
                p1_proj.x = width - 1;
            }
            if (p0_proj.y >= height) {
                p0_proj.y = height - 1;
            }
            if (p1_proj.y >= height) {
                p1_proj.y = height - 1;
            }

            lineDrawer->line(p0_proj, p1_proj, WHITE);

			if (xmlSVG) {
            	file << "<line x1=\"" << p0_proj.x << "\" y1=\""
                     << height - p0_proj.y << "\" x2=\"" << p1_proj.x
                     << "\" y2=\"" << height - p1_proj.y
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

//void
//Renderer::fillBottomFlatTriangle()
//{
//    Point2D vertex0(100, 100);
//    Point2D vertex1(50, 50);
//    Point2D vertex2(150, 50);
//
//    lineDrawer->line(vertex0, vertex1, PURPLE);
//    lineDrawer->line(vertex2, vertex0, PURPLE);
//    lineDrawer->line(vertex1, vertex2, PURPLE);
//
//
//    float invslope1 = (100 - 50) / (100 - 50);
//    float invslope2 = (150 - 100) / (100 - 50);
//
//    unsigned int curx1 = 50;
//    unsigned int curx2 = 150;
//
//    for (unsigned int scanline = vertex1.y; scanline <= vertex0.y; ++scanline) {
//        lineDrawer->line((unsigned int)curx1, scanline, (unsigned int)curx2, scanline, GREEN);
//        curx1 += invslope1;
//        curx2 -= invslope2;
//    }
//}

