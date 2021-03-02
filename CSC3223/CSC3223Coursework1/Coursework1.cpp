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


void createStarfield(Renderer* renderer) {
	OGLMesh* sField = new OGLMesh();
	sField->SetVertexPositions({ Vector3(0,0,0) });
	sField->SetVertexColours({ Vector4(1 ,1 ,1 ,1) });
	sField->SetPrimitiveType(GeometryPrimitive::Points);
	renderer->AddRenderObject(new RenderObject(sField));
	sField->UploadToGPU();
	
	
	for (int i = 0; i < 10000; i++) {
		int x = (rand() % 1000) - 500;
		int y = (rand() % 1000) - 500;
		int z = (rand() % 1000) - 100;


		Matrix4 starTranslation = Matrix4::Translation(Vector3(x, y, z));
		renderer->AddRenderObject(new RenderObject(sField, starTranslation));
	}
	
}

RenderObject* createAsteroidLeft(Renderer* renderer) {
	OGLMesh* asteroidLeft = new OGLMesh();

	
	
	
	asteroidLeft->SetVertexPositions({ Vector3(20,30,-20),Vector3(40,0,0),Vector3(0,0,0),Vector3(0,0,-40),Vector3(40,0,-40),Vector3(40,0,0)});
	asteroidLeft->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	
	
	
	std::vector<Vector4> interpolatedColours = { Vector4(1,0,0,0) };

	for (int i = 0; i < 2; i++) {
		interpolatedColours.push_back({ Vector4(1, 0, 0, 0)});
		interpolatedColours.push_back({ Vector4(0, 1, 0, 0)});
		interpolatedColours.push_back({Vector4(0, 0, 1, 0) });
	}
	asteroidLeft->SetVertexColours(interpolatedColours);
	asteroidLeft->UploadToGPU();


	Matrix4 asteroidMatrixLeft = Matrix4::Translation(Vector3(-150, 10, -50)) *
		Matrix4::Rotation(5 * 10, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -1));




	RenderObject* asteroidPointerLeft;
	asteroidPointerLeft = new RenderObject(asteroidLeft, asteroidMatrixLeft);
	return  asteroidPointerLeft;

}
RenderObject* createAsteroidRight(Renderer* renderer) {
	OGLMesh* asteroidRight = new OGLMesh();


	asteroidRight->SetVertexPositions({ Vector3(20,-30,-20),Vector3(40,0,0),Vector3(0,0,0),Vector3(0,0,-40),Vector3(40,0,-40),Vector3(40,0,0) });
	asteroidRight->SetPrimitiveType(GeometryPrimitive::TriangleFan);
	std::vector<Vector4> interpolatedColours = { Vector4(1,0,0,0) };

	for (int i = 0; i < 2; i++) {
		interpolatedColours.push_back({ Vector4(1, 0, 0, 0) });
		interpolatedColours.push_back({ Vector4(0, 1, 0, 0) });
		interpolatedColours.push_back({ Vector4(0, 0, 1, 0) });
	}


	asteroidRight->SetVertexColours(interpolatedColours);
	asteroidRight->UploadToGPU();


	Matrix4 asteroidMatrixRight = Matrix4::Translation(Vector3(-150, 10, -50)) *
		Matrix4::Rotation(5 * 10, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -1));


	RenderObject* asteroidPointerRight;
	asteroidPointerRight = new RenderObject(asteroidRight, asteroidMatrixRight);
	return  asteroidPointerRight;
}

void createPlanetMesh(Renderer* renderer) {
	OGLMesh* sphere = new OGLMesh("sphere.msh");
	
	sphere->SetPrimitiveType(GeometryPrimitive::TriangleStrip);
	std::vector<Vector4> red = { Vector4(1,0,0,1) };

	for (int i = 0; i < 99; i++) {
		red.push_back({ Vector4(1,0,0,1) });
	}
	sphere->SetVertexColours(red);
	sphere->UploadToGPU();
	

	Matrix4 planetMeshMatrix = Matrix4::Translation(Vector3(10, 10, -200)) *
	Matrix4::Rotation(5 * 10, Vector3(0, 0, 1)) *
	Matrix4::Scale(Vector3(50, 50, -60));


			
	renderer->AddRenderObject(new RenderObject(sphere, planetMeshMatrix));


	
}


void createShipPanels(Renderer* renderer) {
	std::vector<Vector4> wingPanelWhite = { Vector4(1,1,1,1) };

	for (int i = 0; i < 19; i++) {
		wingPanelWhite.push_back({ Vector4(1,1,1,1) });
	}

	std::vector < Vector2 > texCoordsWingPanel =
	{ Vector2(0, 0), Vector2(10, 0), Vector2(5, 10) };
	for (int i = 0; i < 6; i++) {
		texCoordsWingPanel.push_back(Vector2(0, 0));
		texCoordsWingPanel.push_back(Vector2(10, 0));
		texCoordsWingPanel.push_back(Vector2(5, 10));
	}

	OGLMesh* wingPanel1 = new OGLMesh();

	wingPanel1->SetVertexPositions({ Vector3(25, 0, 0),Vector3(15,25,0),Vector3(37.5,25,0),Vector3(25,0,0), Vector3(37.5,25,0),Vector3(45,0,0),Vector3(25,0,0),
		Vector3(45,0,0),Vector3(37.5,-25,0),Vector3(25,0,0),Vector3(37.5,-25,0) ,Vector3(15,-25,0),Vector3(25,0,0),Vector3(15,-25,0) ,Vector3(7.5,0,0),
		Vector3(25,0,0), Vector3(7.5,0,0),Vector3(15,25,0),Vector3(25,0,0) });


	wingPanel1->SetVertexColours(wingPanelWhite);
	wingPanel1->SetVertexTextureCoords(texCoordsWingPanel);

	wingPanel1->UploadToGPU();
	wingPanel1->SetPrimitiveType(GeometryPrimitive::Triangles);

	Matrix4 wingPanel1Mat = Matrix4::Translation(Vector3(10, 10, -25)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -100));


	RenderObject* renderObj = new RenderObject(wingPanel1, wingPanel1Mat);
	renderer->AddRenderObject(renderObj);


	TextureBase* newTex = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex, true, true);


	renderObj->SetBaseTexture(newTex);





	OGLMesh* wingPanel2 = new OGLMesh();

	wingPanel2->SetVertexPositions({ Vector3(25, 0, 0),Vector3(15,25,0),Vector3(37.5,25,0),Vector3(25,0,0),
		Vector3(37.5,25,0),Vector3(45,0,0),Vector3(25,0,0),Vector3(45,0,0),Vector3(37.5,-25,0),Vector3(25,0,0),
		Vector3(37.5,-25,0) ,Vector3(15,-25,0),Vector3(25,0,0),Vector3(15,-25,0) ,Vector3(7.5,0,0),Vector3(25,0,0),
		Vector3(7.5,0,0),Vector3(15,25,0),Vector3(25,0,0) });


	wingPanel2->SetVertexColours(wingPanelWhite);
	wingPanel2->SetVertexTextureCoords(texCoordsWingPanel);

	wingPanel2->UploadToGPU();
	wingPanel2->SetPrimitiveType(GeometryPrimitive::Triangles);


	Matrix4 wingPanel2Mat = Matrix4::Translation(Vector3(10, 10, -20)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -100));


	RenderObject* renderObj2 = new RenderObject(wingPanel2, wingPanel2Mat);
	renderer->AddRenderObject(renderObj2);


	TextureBase* newTex2 = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex2);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex2, true, true);

	renderObj2->SetBaseTexture(newTex2);



	//wing2

	OGLMesh* wingPanel3 = new OGLMesh();

	wingPanel3->SetVertexPositions({ Vector3(25, 0, 0),Vector3(15,25,0),Vector3(37.5,25,0),Vector3(25,0,0), Vector3(37.5,25,0),Vector3(45,0,0),
		Vector3(25,0,0),Vector3(45,0,0),Vector3(37.5,-25,0),Vector3(25,0,0),Vector3(37.5,-25,0) ,Vector3(15,-25,0),Vector3(25,0,0),Vector3(15,-25,0) ,
		Vector3(7.5,0,0),Vector3(25,0,0), Vector3(7.5,0,0),Vector3(15,25,0),Vector3(25,0,0) });


	wingPanel3->SetVertexColours(wingPanelWhite);
	wingPanel3->SetVertexTextureCoords(texCoordsWingPanel);
	wingPanel3->UploadToGPU();
	wingPanel3->SetPrimitiveType(GeometryPrimitive::Triangles);



	Matrix4 wingPanel3Mat = Matrix4::Translation(Vector3(10, 10, 0)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -100));


	RenderObject* renderObj3 = new RenderObject(wingPanel3, wingPanel3Mat);
	renderer->AddRenderObject(renderObj3);


	TextureBase* newTex3 = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex3);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex3, true, true);

	renderObj3->SetBaseTexture(newTex3);



	OGLMesh* wingPanel4 = new OGLMesh();

	wingPanel4->SetVertexPositions({ Vector3(25, 0, 0),Vector3(15,25,0),Vector3(37.5,25,0),Vector3(25,0,0), Vector3(37.5,25,0),Vector3(45,0,0),
		Vector3(25,0,0),Vector3(45,0,0),Vector3(37.5,-25,0),Vector3(25,0,0),Vector3(37.5,-25,0) ,Vector3(15,-25,0),Vector3(25,0,0),Vector3(15,-25,0) ,
		Vector3(7.5,0,0),Vector3(25,0,0), Vector3(7.5,0,0),Vector3(15,25,0),Vector3(25,0,0) });

	wingPanel4->SetVertexColours(wingPanelWhite);
	wingPanel4->SetVertexTextureCoords(texCoordsWingPanel);

	wingPanel4->UploadToGPU();
	wingPanel4->SetPrimitiveType(GeometryPrimitive::Triangles);


	Matrix4 wingPanel4Mat = Matrix4::Translation(Vector3(10, 10, 5)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -100));


	RenderObject* renderObj4 = new RenderObject(wingPanel4, wingPanel4Mat);
	renderer->AddRenderObject(renderObj4);


	TextureBase* newTex4 = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex4);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex4, true, true);

	renderObj4->SetBaseTexture(newTex4);

}
void createWingWidthPanels(Renderer* renderer) {
	OGLMesh* wingpWidthPanel = new OGLMesh();


	std::vector<Vector4> wingWidthPanelWhite = { Vector4(1,1,1,1) };

	for (int i = 0; i < 36; i++) {
		wingWidthPanelWhite.push_back({ Vector4(1,1,1,1) });
	}

	std::vector < Vector2 > texCoordsWidthPanel =
	{ Vector2(0, 0), Vector2(10, 0), Vector2(5, 10) };
	for (int i = 0; i < 12; i++) {
		texCoordsWidthPanel.push_back(Vector2(0, 0));
		texCoordsWidthPanel.push_back(Vector2(10, 0));
		texCoordsWidthPanel.push_back(Vector2(5, 10));
	}

	wingpWidthPanel->SetVertexPositions({ Vector3(15,25,0),Vector3(15,25,-5), Vector3(37.5,25,0),Vector3(37.5,25,0),Vector3(37.5,25,-5),Vector3(15,25,-5),Vector3(37.5,25,-5),Vector3(45,0,-5),
		Vector3(37.5,25,0),Vector3(37.5,25,0),Vector3(45,0,0),Vector3(45,0,-5),Vector3(45,0,0),Vector3(45,0,-5),Vector3(37.5,-25,-5),Vector3(37.5,-25,-5),Vector3(37.5,-25,0),
		Vector3(45,0,0),Vector3(37.5,-25,-5),Vector3(37.5,-25,0),Vector3(15,-25,-5),Vector3(15,-25,0),Vector3(15,-25,-5),Vector3(37.5,-25,0),
		Vector3(15,-25,0),Vector3(15,-25,-5),Vector3(7.5,0,-5),Vector3(7.5,0,0),Vector3(7.5,0,-5),Vector3(15,-25,0),Vector3(7.5,0,0),Vector3(7.5,0,-5),Vector3(15,25,-5),Vector3(15,25,0)
		,Vector3(15,25,-5),Vector3(7.5,0,0) });

	wingpWidthPanel->SetVertexColours(wingWidthPanelWhite);
	wingpWidthPanel->SetVertexTextureCoords(texCoordsWidthPanel);

	wingpWidthPanel->UploadToGPU();
	wingpWidthPanel->SetPrimitiveType(GeometryPrimitive::Triangles);



	Matrix4 wingWidthPanelMat = Matrix4::Translation(Vector3(10, 10, -25)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, -1));


	RenderObject* renderObjWigWidthPanel = new RenderObject(wingpWidthPanel, wingWidthPanelMat);
	renderer->AddRenderObject(renderObjWigWidthPanel);


	TextureBase* newTexWingWidthPanel = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTexWingWidthPanel);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTexWingWidthPanel, true, true);


	renderObjWigWidthPanel->SetBaseTexture(newTexWingWidthPanel);




	OGLMesh* wingpWidthPanel3 = new OGLMesh();
	wingpWidthPanel3->SetVertexPositions({ Vector3(15,25,0),Vector3(15,25,-5), Vector3(37.5,25,0),Vector3(37.5,25,0),Vector3(37.5,25,-5),Vector3(15,25,-5),Vector3(37.5,25,-5),
		Vector3(45,0,-5),Vector3(37.5,25,0),Vector3(37.5,25,0),Vector3(45,0,0),Vector3(45,0,-5),
		Vector3(45,0,0),Vector3(45,0,-5),Vector3(37.5,-25,-5),Vector3(37.5,-25,-5),Vector3(37.5,-25,0),Vector3(45,0,0),
		Vector3(37.5,-25,-5),Vector3(37.5,-25,0),Vector3(15,-25,-5),Vector3(15,-25,0),Vector3(15,-25,-5),Vector3(37.5,-25,0),
		Vector3(15,-25,0),Vector3(15,-25,-5),Vector3(7.5,0,-5),Vector3(7.5,0,0),Vector3(7.5,0,-5),Vector3(15,-25,0),Vector3(7.5,0,0),Vector3(7.5,0,-5)
		,Vector3(15,25,-5),Vector3(15,25,0),Vector3(15,25,-5),Vector3(7.5,0,0) });


	wingpWidthPanel3->SetVertexColours(wingWidthPanelWhite);
	wingpWidthPanel3->SetVertexTextureCoords(texCoordsWidthPanel);

	wingpWidthPanel3->UploadToGPU();
	wingpWidthPanel3->SetPrimitiveType(GeometryPrimitive::Triangles);




	Matrix4 wingWidthPanel3Mat = Matrix4::Translation(Vector3(10, 10, 0)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(Vector3(1, 1, -1)));


	RenderObject* renderObjWingWidth3 = new RenderObject(wingpWidthPanel3, wingWidthPanel3Mat);
	renderer->AddRenderObject(renderObjWingWidth3);


	TextureBase* newTexWingWidth3 = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTexWingWidth3);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTexWingWidth3, true, true);

	renderObjWingWidth3->SetBaseTexture(newTexWingWidth3);

}

void createCenterShip(Renderer* renderer) {
	std::vector < Vector2 > texCoordsCenterShip =
	{ Vector2(0, 0), Vector2(10, 0), Vector2(5, 10) };
	for (int i = 0; i < 8; i++) {
		texCoordsCenterShip.push_back(Vector2(0, 0));
		texCoordsCenterShip.push_back(Vector2(10, 0));
		texCoordsCenterShip.push_back(Vector2(5, 10));
	}

	OGLMesh* centerShip = new OGLMesh();

	centerShip->SetVertexPositions({ Vector3(20, 0, -5), Vector3(20, 0, -25), Vector3(25,-5,-15),Vector3(30, 0, -5),Vector3(30, 0, -25),
		Vector3(25,-5,-15),Vector3(20, 0, -5),Vector3(30, 0, -5),Vector3(25,-5,-15) ,Vector3(20, 0, -25),Vector3(30, 0, -25),Vector3(25,-5,-15),Vector3(20, 0, -5),
		Vector3(20, 0, -25), Vector3(25,5,-15),Vector3(30, 0, -5),Vector3(30, 0, -25),Vector3(25,5,-15),
		Vector3(20, 0, -5),Vector3(30, 0, -5),Vector3(25,5,-15),Vector3(20, 0, -25),Vector3(30, 0, -25),Vector3(25,5,-15) });

	std::vector<Vector4> white = { Vector4(1,1,1,1) };

	for (int i = 0; i < 24; i++) {
		white.push_back({ Vector4(1,1,1,1) });
	}
	centerShip->SetVertexTextureCoords(texCoordsCenterShip);
	centerShip->SetVertexColours(white);

	centerShip->UploadToGPU();
	centerShip->SetPrimitiveType(GeometryPrimitive::Triangles);



	Matrix4 centerShipMat = Matrix4::Translation(Vector3(10, 10, 5)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, 1));


	RenderObject* renderObj3 = new RenderObject(centerShip, centerShipMat);
	renderer->AddRenderObject(renderObj3);


	TextureBase* newTex3 = OGLTexture::RGBATextureFromFilename("brick.png");
	renderer->EnableBilinearFiltering(*(OGLTexture*)newTex3);
	renderer->EnableTextureRepeating(*(OGLTexture*)newTex3, true, true);
	renderObj3->SetBaseTexture(newTex3);
}


void createShip(Renderer* renderer) {
	createShipPanels(renderer);
	createWingWidthPanels(renderer);
	createCenterShip(renderer);
}

RenderObject* createSimpleShip(Renderer* renderer) {
	OGLMesh* simpleShip = new OGLMesh();

	simpleShip->SetVertexPositions({Vector3(-20,0,0),Vector3(-10,0,5),Vector3(-10,-10,0),Vector3(-10,0,5),Vector3(-10,10,0),Vector3(0,0,0) });

	std::vector<Vector4> white = { Vector4(1,1,1,0) };

	for (int i = 0; i < 5; i++) {
		white.push_back({ Vector4(1,1,1,0) });
	}
	simpleShip->SetVertexColours(white);

	simpleShip->UploadToGPU();
	simpleShip->SetPrimitiveType(GeometryPrimitive::Triangles);



	Matrix4 simpleShipMat = Matrix4::Translation(Vector3(10, 10, 5)) *
		Matrix4::Rotation(0, Vector3(0, 0, 1)) *
		Matrix4::Scale(Vector3(1, 1, 1));


	RenderObject* simpleShipRenderObj = new RenderObject(simpleShip, simpleShipMat);

	return  simpleShipRenderObj;

}
void writeName(Renderer* renderer) {
	OGLMesh* btopTri =
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
			{ Vector3(-70 , -30 , -200) ,Vector3(-70 ,0 ,-200) ,Vector3(-50 ,-15 ,-200) },
			{ Vector4(1 ,0 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) });
	renderer->AddRenderObject(new RenderObject(btopTri));
	
	OGLMesh* bBottomTri =
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
			{ Vector3(-70 ,0 ,-200),Vector3(-70 ,40 ,-200),Vector3(-50 ,20 ,-200) },
			{ Vector4(1 ,0 ,1 ,1),Vector4(1 ,0 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) });
	renderer->AddRenderObject(new RenderObject(bBottomTri));
	


	OGLMesh* r =
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
			{ Vector3(-30 , 0 , -200) ,Vector3(-30 ,40 ,-200) ,Vector3(-10 ,20 ,-200) },
			{ Vector4(1 ,0 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) , Vector4(0 ,0 ,1 ,1) });
	renderer->AddRenderObject(new RenderObject(r));

	OGLMesh* rLines =
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
			{ Vector3(-30.5 , 0 , 0) ,Vector3(-30.5 ,-30 ,0),Vector3(-30.5 , 0 , 0),Vector3(-10 ,-30 ,0) },
			{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), //a new vector !
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1) }, false);
	renderer->AddRenderObject(new RenderObject(rLines));

	OGLMesh* a =
		(OGLMesh*)RasterisationMesh::CreateTriangleFromPoints(
			{ Vector3(10 ,0 ,-200),Vector3(30 ,40 ,-200),Vector3(50 ,0 ,-200) },
			{ Vector4(1 ,0 ,1 ,1),Vector4(1 ,0 ,0 ,1) ,Vector4(0 ,1 ,0 ,1) });
	renderer->AddRenderObject(new RenderObject(a));

	OGLMesh* aLines =
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
			{ Vector3(10 , 0 , 0) ,Vector3(0 ,-30 ,0),Vector3(50 , 0 , 0),Vector3(60 ,-30 ,0) },
			{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), //a new vector !
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1) }, false);
	renderer->AddRenderObject(new RenderObject(aLines));

	OGLMesh* d =
		(OGLMesh*)RasterisationMesh::CreateLineFromPoints(
			{ Vector3(80 , -30 , 0) ,Vector3(80 ,40 ,0),Vector3(80 ,40 ,0),Vector3(100 ,37 ,0),Vector3(100 ,37 ,0),Vector3(110 ,30 ,0),Vector3(110 ,30 ,0),
			Vector3(115 ,25 ,0),Vector3(115 ,25 ,0),Vector3(120 ,20 ,0),Vector3(120 ,20 ,0),Vector3(120 ,10 ,0)
			,Vector3(80 , -30 , 0),Vector3(100 , -27,0),Vector3(100 , -27,0),Vector3(110 ,-20 ,0),Vector3(110 ,-20 ,0),Vector3(115 ,-15 ,0),Vector3(115 ,-15 ,0),
			Vector3(120 ,-10 ,0),Vector3(120 ,-10 ,0),Vector3(120 ,10 ,0) },
			{ Vector4(1, 0, 0, 1), Vector4(0, 1, 0, 1), //a new vector !
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1),
			Vector4(0, 0, 1, 1), Vector4(1, 0, 1, 1) }, false);
	renderer->AddRenderObject(new RenderObject(d));

}



int main() {
	Window* w = Window::CreateGameWindow("CSC3223 Coursework 1");
	bool state = true;
	bool stateAlpha = true;
	
	if (!w->HasInitialised()) {
		return -1;
	}
	w->GetScreenSize();
	w->LockMouseToWindow(true);
	
	w->ShowOSPointer(false);
	//w->SetFullScreen(true);
	Renderer* renderer = new Renderer(*w);

	renderer->SetProjectionMatrix(Matrix4::Perspective(1, 1000, w->GetScreenAspect(), 45.0f));


	createPlanetMesh(renderer);
	createStarfield(renderer);
	createShip(renderer);
	createSimpleShip(renderer);

	RenderObject* spinningAsteroidLeft = createAsteroidLeft(renderer);
	renderer->AddRenderObject(spinningAsteroidLeft);
	
	renderer->EnableDepthBuffer(state);
	renderer->EnableBlending(true);

	RenderObject* spinningAsteroidRight = createAsteroidRight(renderer);
	renderer->AddRenderObject(spinningAsteroidRight);

	RenderObject* simpleShipRenderObj = createSimpleShip(renderer);
	renderer->AddRenderObject(simpleShipRenderObj);

	Vector3 viewPosition(0, 0, 0);
	Vector2 cam = Window::GetMouse()->GetRelativePosition();
	
	
	Vector3 xRotation(0,1,0);
	Vector3 xRotationAxis(0,1,0);
	Vector3 yRotation(1, 0, 0);
	Vector3 yRotationAxis(1,0,0);

	string depthBufferText = "Depth Buffer: Enabled";
	string bufferModeText = "Depth Buffer Mode: ";
	string alphaModeText = "Alpha Blending Mode: ";
	string alphaBlendText = "Alpha Blending: Enabled";


	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KEYBOARD_ESCAPE)) {

		float time = w->GetTimer()->GetTimeDelta();

		//spinning asteroid
		if (spinningAsteroidLeft != nullptr) {
			spinningAsteroidLeft->SetTransform(spinningAsteroidLeft->GetTransform() * Matrix4::Rotation(20 * time, Vector3(1, 0, 0)));
		}
		if (spinningAsteroidRight != nullptr) {
			spinningAsteroidRight->SetTransform(spinningAsteroidRight->GetTransform() * Matrix4::Rotation(20 * time, Vector3(1, 0, 0)));
		}
		if (simpleShipRenderObj != nullptr) {
			simpleShipRenderObj->SetTransform(simpleShipRenderObj->GetTransform() * Matrix4::Translation(Vector3(-10 * time, 0, 0)));
		}
		
		//makes background black
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT);


		renderer->Update(time);
		renderer->DrawString("Bradley Ford's Coursework 1!", Vector2(10, 10));
		
		renderer->DrawString(depthBufferText, Vector2(10, 30));
		renderer->DrawString(bufferModeText, Vector2(10, 70));

		renderer->DrawString(alphaBlendText, Vector2(10, 50));
		renderer->DrawString(alphaModeText, Vector2(10, 90));

		renderer->SetViewMatrix(Matrix4::Translation(viewPosition) * Matrix4::Rotation(xRotation.x, xRotationAxis) * Matrix4::Rotation(yRotation.y, yRotationAxis));
		renderer->Render();

		if (cam.x - Window::GetMouse()->GetRelativePosition().x > 0) {
			xRotation.x -= 2.0f;
		}
		if (cam.x - Window::GetMouse()->GetRelativePosition().x < 0) {
			xRotation.x += 2.0f;
		}
		if (cam.y - Window::GetMouse()->GetRelativePosition().y > 0) {
			yRotation.y -= 2.0f;
		}
		if (cam.y - Window::GetMouse()->GetRelativePosition().y < 0) {
			yRotation.y += 2.0f;
		}



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
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
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
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
			viewPosition.z += 1.0f;

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
			viewPosition.z -= 1.0f;

		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F1)) {

			if (state == false) {
				depthBufferText = "Depth Buffer : Enabled";
				glEnable(GL_DEPTH_TEST);
				state = true;
			}
			else if (state == true) {
				depthBufferText = "Depth Buffer : Disabled";
				glDisable(GL_DEPTH_TEST);
				state = false;
			}
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F2)) {

			bufferModeText = "Depth Buffer Mode: Less";
			glDepthFunc(GL_LESS);
			
		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F3)) {

			bufferModeText = "Depth Buffer Mode: Greater";
			glDepthFunc(GL_GREATER);

		}
		if (Window::GetKeyboard()->KeyDown(KEYBOARD_F4)) {

			bufferModeText = "Depth Buffer Mode: Not Equal";
			glDepthFunc(GL_NOTEQUAL);

		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F5)) {

			if (stateAlpha == false) {
				alphaBlendText = "Alpha Blending : Enabled";
				glEnable(GL_BLEND);
				stateAlpha = true;
			}
			else if(stateAlpha == true){
				alphaBlendText = "Alpha Blending : Disabled";
				glDisable(GL_BLEND);
				stateAlpha = false;
			}
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F6)) {
			alphaModeText = "Alpha Blending Mode: Linear";
			renderer->SetBlendToLinear();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F7)) {
			alphaModeText = "Alpha Blending Mode: Additive";
			renderer->SetBlendToAdditive();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F8)) {
			alphaModeText = "Alpha Blending Mode: Invert";
			renderer->SetBlendToInvert();
		}
		if (Window::GetKeyboard()->KeyPressed(KEYBOARD_F9)) {
			alphaModeText = "";
			bufferModeText = "";
			depthBufferText = "To Go Back To Starfield Restart Program";
			alphaBlendText = "";

			simpleShipRenderObj = nullptr;
			spinningAsteroidLeft = nullptr;
			spinningAsteroidRight = nullptr;
		
			viewPosition.z = -300;
			viewPosition.x = -50;
			viewPosition.y = 0;
			xRotation.x = 0;
			yRotation.y = 0;
			renderer->DeleteAllRenderObjects();
			writeName(renderer);
		}

	
		renderer->SetViewMatrix(Matrix4::Translation(viewPosition));

		w->SetTitle(std::to_string(time));
	}

	delete renderer;

	Window::DestroyGameWindow();
}