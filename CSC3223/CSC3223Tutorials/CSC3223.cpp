#include "RasterisationMesh.h"
#include "../../Common/Window.h"
#include "../../Common/TextureLoader.h"
#include "../../Common/Vector3.h"
#include "../../Common/Vector4.h"
#include "../../Common/MeshGeometry.h"
#include "../../Common/Maths.h"

#include "../../Plugins/OpenGLRendering/OGLRenderer.h"
#include "../../Plugins/OpenGLRendering/OGLMesh.h"
#include "../../Plugins/OpenGLRendering/OGLShader.h"
#include "../../Plugins/OpenGLRendering/OGLTexture.h"

#include "Renderer.h"


using namespace NCL;
using namespace CSC3223;


void Tutorial1(Renderer* renderer) {
	//Points
	OGLMesh* points = new OGLMesh(); //Creating a new mesh to store some vertices called points.
	points->SetVertexPositions({ Vector3(50,50, 0), Vector3(30,10,0),Vector3(200,70,0) }); //setting the positions of 3 vectices in the 800x600 screen space.
	points->SetPrimitiveType(GeometryPrimitive::Points);//Setting the type of objects in the mesh to points.
	points->UploadToGPU();//initialises all of the vertex buffers and vertex attributes so we dont have to. (think back to the mirrors edge example from first lecture)
	renderer->AddRenderObject(new RenderObject(points)); //adds points to what needs to be rendered.

	//Lines
	OGLMesh* lines = new OGLMesh();

	lines->SetVertexPositions({Vector3(600,50,0),Vector3(680,180,0),Vector3(680,50,0),Vector3(600,180,0)});
	lines->SetPrimitiveType(GeometryPrimitive::Lines);
	lines->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(lines));

	//Triangle
	OGLMesh* tris = new OGLMesh();

	tris->SetVertexPositions({Vector3(50,450,0),Vector3(250,450,0),Vector3(150,350,0)});
	tris->SetPrimitiveType(GeometryPrimitive::Triangles);
	tris->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(tris));

	//Triangle Strips
	OGLMesh* triStrip = new OGLMesh();
	triStrip->SetVertexPositions({Vector3(600,450,0),Vector3(700,450,0),Vector3(650,350,0),Vector3(750,350,0)});
	triStrip->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	triStrip->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(triStrip));

	//Triangle Fan
	OGLMesh* triFan = new OGLMesh();
	triFan->SetVertexPositions({ Vector3(350, 300, 0),Vector3(375,350,0),Vector3(425,350,0),Vector3(450,300,0),Vector3(425,250,0),Vector3(375,250,0) });
	triFan->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	triFan->UploadToGPU();
	renderer->AddRenderObject(new RenderObject(triFan));


}
void Tutorial2(Renderer* renderer) { // Normal OpenGL Primitives
	// Normal OpenGL mesh in top left
		 OGLMesh * lines = new OGLMesh();
	 lines -> SetVertexPositions({ Vector3(150 , 50 , 0) ,
	 Vector3(180 ,80 ,0) , Vector3(100 ,200 ,0) , Vector3(150 ,150 ,0) });
	
		 lines -> SetVertexColours({ Vector4(1 ,0 ,0 ,1) ,
		 Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) , Vector4(1 ,0 ,1 ,1) });
	
		 lines -> SetPrimitiveType(GeometryPrimitive::Lines);
	 lines -> UploadToGPU();
	 renderer->AddRenderObject(new RenderObject(lines));
	 // And another OpenGL mesh in the top right
		 OGLMesh * tris = new OGLMesh();
	 tris -> SetVertexPositions({ Vector3(550 , 200 , 0) ,
	 Vector3(750 , 200 , 0) , Vector3(650 , 100 , 0) });
	
		 tris -> SetVertexColours({ Vector4(1 ,0 ,0 ,1) ,
		 Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) });
	
		 tris -> SetPrimitiveType(GeometryPrimitive::Triangles);
	 tris -> UploadToGPU();
	 renderer->AddRenderObject(new RenderObject(tris));

	 OGLMesh* rasterLine =
		 (OGLMesh*)RasterisationMesh::CreateLineFromPoints(
			 { Vector3(150, 350, 0), Vector3(180, 380, 0),
			Vector3(100, 500, 0), Vector3(150, 450, 0) },
			 { Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), //a new vector !
			 Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1) }, false);

	 OGLMesh* rasterTri =
		 (OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
			 { Vector3(550, 400, 0), Vector3(750, 380, 0), Vector3(650, 300, 0) },
			 { Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) });
			renderer->AddRenderObject(new RenderObject(rasterTri));}void Tutorial4(Renderer* renderer) {
	OGLMesh* tri = new OGLMesh();
	tri->SetVertexPositions(
		{ Vector3(-1, 0, 0), Vector3(1, 0, 0), Vector3(0, 1, 0) });
	tri->SetVertexColours(
		 { Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), Vector4(0, 0, 1, 1) });
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();	for (int y = 0; y < 5; ++y) {
		 for (int x = 0; x < 5; ++x) {
			Matrix4 translate = Matrix4::Translation(
			Vector3((x + 1) * 130, (y + 1) * 120, 0));
			Matrix4 rotate = Matrix4::Rotation(
				 ((y * 5) + x) * 10, Vector3(0, 0, 1));
			Matrix4 scale = Matrix4::Scale(Vector3(50, 50, 50) / (1 + y));
			Matrix4 modelMat = translate * rotate * scale;
			renderer->AddRenderObject(new RenderObject(tri, modelMat));
			
		}
			}}
void Tutorial5(Renderer* renderer) {
	OGLMesh* tri = new OGLMesh("Cube.msh");
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();
	
		for (int y = -4; y < 3; ++y) {
		for (int x = -4; x < 3; ++x) {
			
			float zAmount = rand() % 30;
			float scaleAmount = ((rand() % 3) + 1);
			
			Matrix4 translate = Matrix4::Translation( Vector3((x + 1) * 10, (y + 1) * 10, -50 - zAmount));
			Matrix4 rotate = Matrix4::Rotation( ((y * 5) + x) * 10, Vector3(0, 0, 1));
			Matrix4 scale = Matrix4::Scale(Vector3(scaleAmount, scaleAmount, scaleAmount));
			
			renderer->AddRenderObject(new RenderObject(tri, translate * rotate * scale));	
		}
	}
}void Tutorial6(Renderer* renderer)
{
	std::vector<Vector4> red = {Vector4(1,0,0,1), Vector4(1,0,0,1), Vector4(1,0,0,1)};
	std::vector<Vector4> blue = {Vector4(0,0,1,1), Vector4(0,0,1,1),Vector4(0,0,1,1)};

	std::vector<Vector3> verts = {Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0)};


	OGLMesh* redTri = new OGLMesh();
	redTri -> SetVertexPositions(verts);
	redTri -> SetVertexColours(red);
	redTri -> SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri -> UploadToGPU();
	
	OGLMesh * blueTri = new OGLMesh();
	blueTri -> SetVertexPositions(verts);
	blueTri -> SetVertexColours(blue);
	blueTri -> SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri -> UploadToGPU();	Matrix4 redModelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
	Matrix4::Scale(Vector3(5, 5, 5));
	Matrix4 blueModelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
	Matrix4::Scale(Vector3(15, 15, 15));
	
	renderer->AddRenderObject(new RenderObject(redTri, redModelMat));
	renderer->AddRenderObject(new RenderObject(blueTri, blueModelMat));
}
void Tutorial7(Renderer* renderer) {
	std::vector <Vector3> verts = {
	Vector3(-1 , -1 ,0) , Vector3(1 , -1 ,0) , Vector3(0 ,1 ,0) };
	std::vector < Vector4 > white = {
	Vector4(1 ,1 ,1 ,1) , Vector4(1 ,1 ,1 ,1) , Vector4(1 ,1 ,1 ,1) };
	
	std::vector < Vector2 > texCoords =
		 { Vector2(0, 0), Vector2(10, 0), Vector2(5, 10) };
	
	OGLMesh * tri = new OGLMesh();
	tri->SetVertexPositions(verts);
	tri->SetVertexColours(white);
	tri->SetVertexTextureCoords(texCoords);
	tri->SetPrimitiveType(GeometryPrimitive::Triangles);
	tri->UploadToGPU();
	
	Matrix4 modelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Rotation(45.0f, Vector3(1, 0, 0)) *
		Matrix4::Scale(Vector3(15, 15, 15));
	
	RenderObject * renderObj = new RenderObject(tri, modelMat);
	renderer->AddRenderObject(renderObj);


	//TextureBase* newTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");
	
	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("NCL.PNG");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex);	renderer->EnableTextureRepeating(*(OGLTexture*)newTex, false, false);		renderObj->SetBaseTexture(newTex);	
	
		
	}void Tutorial8(Renderer* renderer)
{
	std::vector < Vector4 > red = { Vector4(1 ,0 ,0 ,0.25) , Vector4(1 ,0 ,0 ,0.33) , Vector4(1 ,0 ,0 ,0.5) };
	std::vector < Vector4 > blue = { Vector4(0 ,0 ,1 ,0.75) , Vector4(0 ,0 ,1 ,0.75) , Vector4(0 ,0 ,1 ,0.75) };
	std::vector<Vector3> verts = { Vector3(-1,-1,0), Vector3(1,-1,0), Vector3(0,1,0) };


	OGLMesh* redTri = new OGLMesh();
	redTri->SetVertexPositions(verts);
	redTri->SetVertexColours(red);
	redTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	redTri->UploadToGPU();

	OGLMesh* blueTri = new OGLMesh();
	blueTri->SetVertexPositions(verts);
	blueTri->SetVertexColours(blue);
	blueTri->SetPrimitiveType(GeometryPrimitive::Triangles);
	blueTri->UploadToGPU();	Matrix4 redModelMat = Matrix4::Translation(Vector3(0, 0, -30)) *
		Matrix4::Scale(Vector3(5, 5, 5));
	Matrix4 blueModelMat = Matrix4::Translation(Vector3(0, 0, -70)) *
		Matrix4::Scale(Vector3(15, 15, 15));

	renderer->AddRenderObject(new RenderObject(redTri, redModelMat));
	renderer->AddRenderObject(new RenderObject(blueTri, blueModelMat));
}
int main() {
	Window*w = Window::CreateGameWindow("CSC3223 Tutorials!");
	if (!w->HasInitialised()) {
		return -1;
	}

	Renderer*	renderer = new Renderer(*w);
	/*float aspect = w->GetScreenAspect();
	Matrix4 proj = Matrix4::Perspective(1.0f, 100.0f, aspect, 45.0f);
	renderer->SetProjectionMatrix(proj);
	*/
	//renderer->SetProjectionMatrix(Matrix4::Perspective(1, 100, w -> GetScreenAspect(), 45.0f));
	Tutorial1(renderer);
		Vector3 viewPosition(0, 0, 0);
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {
		float time = w->GetTimer()->GetTimeDelta();

		//renderer->EnableDepthBuffer(true);		//renderer->EnableBlending(true);
		renderer->Update(time);
		//renderer->SetBlendToLinear();
		//renderer->SetBlendToAdditive();
		//renderer->SetBlendToInvert()

		renderer->DrawString("OpenGL Rendering!", Vector2(10, 10));

		renderer->Render();

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_HOME)) {
			w->SetFullScreen(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_END)) {
			w->SetFullScreen(false);
		}
		if (Window::GetKeyboard()-> KeyDown(KEYBOARD_A)) {
			viewPosition.x += 1.0f;
		
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
			 viewPosition.x -= 1.0f;
			
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
			 viewPosition.y -= 1.0f;
			
		}
		 if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
			 viewPosition.y += 1.0f;
			
		}
		if (Window::GetKeyboard() -> KeyDown(KEYBOARD_W)) {
			  viewPosition.z += 1.0f;
			 
		 }
		 if (Window::GetKeyboard() -> KeyDown(KEYBOARD_S)) {
			  viewPosition.z -= 1.0f;
			 		 }		 if (Window::GetKeyboard()->KeyDown(KEYBOARD_F11)) {
			 renderer->WriteDepthBuffer(" Depth .png ");		 }
		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));
		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}