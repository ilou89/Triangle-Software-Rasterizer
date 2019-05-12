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

/* Line sweeping method using Bresenham */
void
Renderer::fillTriangle(Point2D v0, Point2D v1, Point2D v2)
{
    std::vector<unsigned int> p0;
    std::vector<unsigned int> p1;
    std::vector<unsigned int> p2;

    if (v0.y > v1.y) {
        std::swap(v0, v1);
    }
    if (v0.y > v2.y) {
        std::swap(v0, v2);
    }
    if (v1.y > v2.y) {
        std::swap(v1, v2);
    }

    /*
     * Get the coordinates of the outline
     * of the triangle
     */
    lineDrawer->line(v0, v1, PURPLE);
    p0 = lineDrawer->getXCoords();
    if (!p0.empty()) {
        p0.pop_back();
    }

    lineDrawer->line(v1, v2, PURPLE);
    p1 = lineDrawer->getXCoords();

    lineDrawer->line(v2, v0, RED);
    p2 = lineDrawer->getXCoords();

    p0.insert(p0.end(), p1.begin(), p1.end());

    /*
     * Horizontal Bresenham between each x coordinates
     * for each height pixel
     */
    int i = 0;
    for (unsigned int y = v0.y; y < v2.y; y++) {
        Point2D pStart(p2[i], y);
        Point2D pEnd(p0[i], y);
        i++;

        lineDrawer->line(pEnd, pStart, GREEN);
    }
    lineDrawer->line(v0, v1, PURPLE);
    lineDrawer->line(v1, v2, PURPLE);
    lineDrawer->line(v2, v0, RED);
    p2 = lineDrawer->getXCoords();
}

/* Barycentric method */
void
Renderer::fillTriangle2(Point2D v0, Point2D v1, Point2D v2)
{

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

void
Renderer::rasterize()
{
    Point2D v0(10, 70);
    Point2D v1(50, 160);
    Point2D v2(70, 80);
    fillTriangle(v0, v1, v2);

    Point2D v3(180, 50);
    Point2D v4(150, 1);
    Point2D v5(70, 180);
    fillTriangle(v3, v4, v5);

    Point2D v6(180, 150);
    Point2D v7(120, 160);
    Point2D v8(130, 180);
    fillTriangle(v6, v7, v8);

    Point2D v9(300, 300);
    Point2D v11(400, 200);
    Point2D v10(200, 200);
    fillTriangle(v9, v10, v11);

    Point2D v12(400, 400);
    Point2D v13(500, 500);
    Point2D v14(300, 500);
    fillTriangle(v12, v13, v14);
}

