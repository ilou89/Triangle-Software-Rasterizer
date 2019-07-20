#include "renderer.h"

const Color RED    = Color(255, 0, 0, 255);
const Color GREEN  = Color(0, 255, 0, 255);
const Color BLUE   = Color(0, 0, 255, 255);
const Color WHITE  = Color(255, 255, 255, 255);
const Color PURPLE = Color(128, 0, 128, 255);

Renderer::Renderer(int choice, Bitmap &bitmap, ModelLoader &model)
 : bmp(bitmap), model(model)
{
    LineDrawerFactory::LineDrawerType type = static_cast<LineDrawerFactory::LineDrawerType>(choice);
    lineDrawer = LineDrawerFactory::makeLineDrawer(type, bitmap);
}

Renderer::~Renderer()
{

}

/* Line sweeping rasterization method using Bresenham */
void
Renderer::fillTriangle(Vec3f v0, Vec3f v1, Vec3f v2, float intensity)
{
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();
    std::vector<unsigned int> p0;
    std::vector<unsigned int> p1;
    std::vector<unsigned int> p2;

    /*
     * Convert to unsigned in order to use bresenham and
     * clip against screen bounds
     */
    Point2D p0_raster;
    p0_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v0.x))));
    p0_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v0.y))));
    Point2D p1_raster;
    p1_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v1.x))));
    p1_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v1.y))));
    Point2D p2_raster;
    p2_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v2.x))));
    p2_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v2.y))));

    if (p0_raster.y > p1_raster.y) {
        std::swap(p0_raster, p1_raster);
    }
    if (p0_raster.y > p2_raster.y) {
        std::swap(p0_raster, p2_raster);
    }
    if (p1_raster.y > p2_raster.y) {
        std::swap(p1_raster, p2_raster);
    }

    //Color color(rand()%255, rand()%255, rand()%255, 255);
    Color color(intensity * 255, intensity * 255, intensity * 255, 255);

    /*
     * Get the coordinates of the outline
     * of the triangles
     */
    lineDrawer->line(p0_raster, p1_raster, color);
    p0 = lineDrawer->getXCoords();
    if (!p0.empty()) {
        p0.pop_back();
    }

    lineDrawer->line(p1_raster, p2_raster, color);
    p1 = lineDrawer->getXCoords();

    lineDrawer->line(p2_raster, p0_raster, color);
    p2 = lineDrawer->getXCoords();

    p0.insert(p0.end(), p1.begin(), p1.end());

    /*
     * Horizontal Bresenham between each x coordinates
     * for each height pixel
     */
    int i = 0;
    for (unsigned int y = p0_raster.y; y < p2_raster.y; y++) {
        Point2D pStart(p2[i], y);
        Point2D pEnd(p0[i], y);
        i++;

        lineDrawer->line(pEnd, pStart, color);
    }

    /* Drawing the outline of the triangles */
    //lineDrawer->line(p0_raster, p1_raster, PURPLE);
    //lineDrawer->line(p1_raster, p2_raster, PURPLE);
    //lineDrawer->line(p2_raster, p0_raster, RED);
}

/* Barycentric rasterization method */
void
Renderer::fillTriangle2(Vec3f v0, Vec3f v1, Vec3f v2, float intensity)
{
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();
    Point2D bbmax(0, 0);
    Point2D bbmin(width - 1, height - 1);

    /*
     * Convert to unsigned in order to use bresenham and
     * clip against screen bounds
     */
    Point2D p0_raster;
    p0_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v0.x))));
    p0_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v0.y))));
    Point2D p1_raster;
    p1_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v1.x))));
    p1_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v1.y))));
    Point2D p2_raster;
    p2_raster.x = std::max(0, std::min(static_cast<int>(width - 1),
                                       static_cast<int>(std::floor(v2.x))));
    p2_raster.y = std::max(0, std::min(static_cast<int>(height - 1),
                                       static_cast<int>(std::floor(v2.y))));

    std::vector<Point2D> triangle;
    triangle.push_back(p0_raster);
    triangle.push_back(p1_raster);
    triangle.push_back(p2_raster);

    for (int i = 0; i < 3; ++i) {
        if (triangle[i].x < bbmin.x) bbmin.x = triangle[i].x;
        if (triangle[i].y < bbmin.y) bbmin.y = triangle[i].y;
        if (triangle[i].x > bbmax.x) bbmax.x = triangle[i].x;
        if (triangle[i].y > bbmax.y) bbmax.y = triangle[i].y;
    }

    Color color(intensity * 255, intensity * 255, intensity * 255, 255);
	Point2D p;
    for(p.y = bbmin.y; p.y <= bbmax.y; ++p.y) {
        for(p.x = bbmin.x; p.x <= bbmax.x; ++p.x) {
            int w0 = edgeFunction(p1_raster, p2_raster, p);
            int w1 = edgeFunction(p2_raster, p0_raster, p);
            int w2 = edgeFunction(p0_raster, p1_raster, p);

            if(w0 >= 0 && w1>= 0 && w2 >= 0) {
                bmp.setPixel(p, color);
            }
        }
    }
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
    float intensity = 0.5f;

    Vec3f v0(10, 70, 0);
    Vec3f v1(50, 160, 0);
    Vec3f v2(70, 80, 0);
    fillTriangle(v0, v1, v2, intensity);

    Vec3f v3(180, 50, 0);
    Vec3f v4(150, 1, 0);
    Vec3f v5(70, 180, 0);
    fillTriangle(v3, v4, v5, intensity);

    Vec3f v6(180, 150, 0);
    Vec3f v7(120, 160, 0);
    Vec3f v8(130, 180, 0);
    fillTriangle(v6, v7, v8, intensity);

    Vec3f v9(300, 300, 0);
    Vec3f v11(400, 200, 0);
    Vec3f v10(200, 200, 0);
    fillTriangle(v9, v10, v11, intensity);

    Vec3f v12(400, 400, 0);
    Vec3f v13(500, 500, 0);
    Vec3f v14(300, 500, 0);
    fillTriangle(v12, v13, v14, intensity);
}

void
Renderer::render()
{
    float intensity;
    Vec3f light_dir(0,0,-1);
    unsigned int width = bmp.getWidth();
    unsigned int height = bmp.getHeight();

    for (int i = 0; i < model.indicesSize(); ++i) {
        std::vector<int> triangle = model.getIndicesAt(i);

        /**
         * Assume that the vertices read from .obj file
         * are already projected and are in screen space,
         * otherwise perspective division would be needed
         */
        Vec3f v0 = model.getVerticesAt(triangle[0]);
        Vec3f v1 = model.getVerticesAt(triangle[1]);
        Vec3f v2 = model.getVerticesAt(triangle[2]);

        Vec3f n = (v2 - v0) ^ (v1 - v0);
        n.normalize();
        intensity = n*light_dir;

        /**
         * Assume that the vertices read from .obj fle
         * are already in NDC space ([-1,1]).
         * Convert them to [0,1] and then in raster space
         */
        v0.x = (v0.x + 1.0f) * width / 2.0f;
        v0.y = (v0.y + 1.0f) * height / 2.0f;
        v1.x = (v1.x + 1.0f) * width / 2.0f;
        v1.y = (v1.y + 1.0f) * height / 2.0f;
        v2.x = (v2.x + 1.0f) * width/ 2.0f;
        v2.y = (v2.y + 1.0f) * height / 2.0f;

        if(intensity > 0) {
            fillTriangle(v0, v1, v2, intensity);
        }
        //if(intensity > 0) {
        //    fillTriangle2(v0, v1, v2, intensity);
        //}
    }
}

int
Renderer::edgeFunction(Point2D &v0, Point2D &v1, Point2D &v2)
{
	return (v1.x - v0.x) * (v2.y - v0.y) - (v1.y - v0.y) * (v2.x - v0.x);
}
