#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Matrix.h"

using namespace ci;
using namespace ci::app;

class FacedBoxApp : public AppNative {
  // ñ èÓïÒÇíËã`
  //  éOäpå`ÇÃí∏ì_ÅAêF
  struct Face {
    Vec3f v1, v2, v3;
    Color color;
  };
  std::vector<Face> faces;

  std::vector<Vec3f> change;
  float rx;
  float ry;
  float rz;

   

public:
  void setup();
  void update();
  void draw();
};

void FacedBoxApp::setup() {
  // ñ èÓïÒÇê∂ê¨
  faces.push_back({ { -1, -1, -1 }, { 1, 1, -1 }, { 1, -1, -1 }, { 0, 1, 1 } });
  faces.push_back({ { -1, -1, -1 }, { -1, 1, -1 }, { 1, 1, -1 }, { 0, 1, 1 } });

  faces.push_back({ { -1, 1, -1 }, { -1, 1, 1 }, { 1, 1, 1 }, { 1, 0, 0 } });
  faces.push_back({ { -1, 1, -1 }, { 1, 1, 1 }, { 1, 1, -1 }, { 1, 0, 0 } });

  faces.push_back({ { 1, -1, -1 }, { 1, 1, -1 }, { 1, 1, 1 }, { 0, 1, 0 } });
  faces.push_back({ { 1, -1, -1 }, { 1, 1, 1 }, { 1, -1, 1 }, { 0, 1, 0 } });

  faces.push_back({ { -1, -1, -1 }, { -1, -1, 1 }, { -1, 1, 1 }, { 0, 0, 1 } });
  faces.push_back({ { -1, -1, -1 }, { -1, 1, 1 }, { -1, 1, -1 }, { 0, 0, 1 } });

  faces.push_back({ { -1, -1, -1 }, { 1, -1, 1 }, { -1, -1, 1 }, { 1, 1, 0 } });
  faces.push_back({ { -1, -1, -1 }, { 1, -1, -1 }, { 1, -1, 1 }, { 1, 1, 0 } });

  faces.push_back({ { 1, 1, 1 }, { -1, 1, 1 }, { -1, -1, 1 }, { 1, 0, 1 } });
  faces.push_back({ { 1, 1, 1 }, { -1, -1, 1 }, { 1, -1, 1 }, { 1, 0, 1 } });
    //|
    change.push_back({1.2,-2,0});
    change.push_back({0,0,0});
    change.push_back({2,0,0});
    change.push_back({4,0,0});
    change.push_back({6,0,0});
    //--
    change.push_back({0,0,0});
    change.push_back({0,2,0});
    change.push_back({0,4,0});
    change.push_back({0,6,0});
    // |
    change.push_back({4,2,0});
    change.push_back({4,4,0});
    change.push_back({4,6,0});
    
    change.push_back({-2,-6,0});
    change.push_back({0,-6,0});
    change.push_back({2,-6,0});
    change.push_back({4,-6,0});
    change.push_back({6,-6,0});
    
    change.push_back({-2,8,0});
    change.push_back({0,8,0});
    change.push_back({2,8,0});
    change.push_back({4,8,0});
    change.push_back({6,8,0});
    
    change.push_back({-4,-4,0});
    change.push_back({-4,-2,0});
    change.push_back({-4,0,0});
    change.push_back({-4,2,0});
    change.push_back({-4,4,0});
    change.push_back({-4,6,0});
    change.push_back({-4,8,0});
    
    
  rx = 0.0f;
  ry = 0.0f;
  rz = 0.0f;

  // êkìxÉoÉbÉtÉ@ÇÃì«Ç›èëÇ´ON
  //gl::enableDepthRead();
  //gl::enableDepthWrite();
  // ÉJÉäÉìÉOON
  // Åuó†ñ ÅvÇï`âÊÇµÇ»ÇÊÇ§Ç…Ç∑ÇÈ
  //gl::enable(GL_CULL_FACE);
}

void FacedBoxApp::update() {
  //rx += 0.01f;
  ry += 0.01f;
  //rz += 0.01f;
    

}

void FacedBoxApp::draw() {
  // clear out the window with black
  gl::clear(Color(0, 0, 0));

  // çsóÒê∂ê¨
  Matrix44f translate = Matrix44f::createTranslation(Vec3f(100.0, 0.0, 700.0));
  Matrix44f scale     = Matrix44f::createScale(Vec3f(50.0, 50.0, 50.0));
  Matrix44f rotate    = Matrix44f::createRotation(Vec3f(rx, ry, rz));

    struct PolyGon{
        Vec2f p1,p2,p3;
        float z;
        Color color;
    };
    std::vector<PolyGon> polygons;
    
  for(size_t h = 0; h < change.size();++h){
    for (size_t i = 0; i < faces.size(); ++i) {
    Face& face = faces[i];
       Matrix44f change_trans = Matrix44f::createTranslation(change[h]);
        
    // ñ ÇÃï`âÊêFê›íË
    gl::color(face.color);

      if(i >= faces.size()) translate = Matrix44f::createTranslation(Vec3f(-500.0, 0.0, 700.0));;
    // çsóÒÇ≈ä|ÇØÇÈ
          auto v1 = translate * scale * rotate * change_trans * face.v1;
          auto v2 = translate * scale * rotate * change_trans * face.v2;
          auto v3 = translate * scale * rotate * change_trans * face.v3;
     

    // ZÇ≈äÑÇÈ
    Vec2f offset = getWindowSize() / 2;
    
    
    Vec2f p1 = Vec2f(v1.x, v1.y) / (v1.z * 0.003f) + offset;
    Vec2f p2 = Vec2f(v2.x, v2.y) / (v2.z * 0.003f) + offset;
    Vec2f p3 = Vec2f(v3.x, v3.y) / (v3.z * 0.003f) + offset;
      
    //外積にもとめるベクトルa,bをとめる.
      Vec2f a = p2 - p1;
      Vec2f b = p3 - p1;
      
      
      float cross = b.cross(a);
      
    // ñ (éOäpå`)ÇÃï`âÊ
    
        if(cross <= 0) continue;
                //gl::drawSolidTriangle(p1, p2, p3);
        float z = (v1.z + v2.z + v3.z) / 3.0;
        PolyGon polygon = {
            p1,p2,p3,
            z,
            face.color
        };
          polygons.push_back(polygon);
      
    }
      std::sort(std::begin(polygons),std::end(polygons),
                [](PolyGon& a,PolyGon& b){
                    return a.z > b.z;
                });
      for(auto& polygon : polygons){
          
          gl::color(polygon.color);
          gl::drawSolidTriangle(polygon.p1,
                                polygon.p2,
                                polygon.p3);
      }
  }
}

CINDER_APP_NATIVE(FacedBoxApp, RendererGl)
