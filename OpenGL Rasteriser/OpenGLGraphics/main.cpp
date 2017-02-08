#include "Renderer.h"
#include "RenderObject.h"

#pragma comment(lib, "nclgl.lib")
int wrap(int i, int shaderLimit) {
	if (i > shaderLimit) {
		i = 1;
	}
	else if (i < 1) {
		i = shaderLimit;
	}
	return i;
}


Shader* changeShader(int i, int j, int k) {
	string vert;
	string frag;
	Shader* texture;
	string geo;
	string tessEva;
	string tessCont;
	if (i == 1) {
		frag = "basicFrag.glsl";
	}
	else if (i == 2) {
		frag = "alphaFrag.glsl";
	}
	else if (i == 3) {
		frag = "vertFrag.glsl";
	}
	else if (i == 4) {
		frag = "texFrag.glsl";
	}
	if (j == 1) {
		vert = "basicVert.glsl";
	}
	else if (j == 2) {
		vert = "shrinkVert.glsl";
	}
	else if (j == 3) {
		vert = "oscillateVert.glsl";
	}
	if (k == 1) {
		geo = "basicGeo.glsl";
	}
	else if (k == 2) {
		geo = "editGeo.glsl";
	}
	
		return texture = new Shader(vert, frag, geo);
	
}

int keyboardInputFrag(int i) {
	int shaderLimit = 4;

	i = wrap(i, shaderLimit);

	if (Keyboard::KeyTriggered(KEY_LEFT)) {
		i--;
		i = wrap(i, shaderLimit);
	}
	if (Keyboard::KeyTriggered(KEY_RIGHT)) {
		i++;
		i = wrap(i, shaderLimit);
	}
	return i;
}
int keyboardInputVert(int j) {
	int shaderLimit = 3;

	j = wrap(j, shaderLimit);

	if (Keyboard::KeyTriggered(KEY_DOWN)) {
		j--;
		j = wrap(j, shaderLimit);
	}
	if (Keyboard::KeyTriggered(KEY_UP)) {
		j++;
		j = wrap(j, shaderLimit);
	}
	return j;
}
int keyboardInputGeo(int k) {
	int shaderLimit = 2;

	k = wrap(k, shaderLimit);

	if (Keyboard::KeyTriggered(KEY_G)) {
		k--;
		k = wrap(k, shaderLimit);
	}
	if (Keyboard::KeyTriggered(KEY_H)) {
		k++;
		k = wrap(k, shaderLimit);
	}
	return k;
}





void main(void) {
	int dimensions = 800;
	Window w = Window(dimensions, dimensions);
	Renderer r(w);

	Mesh*	m = Mesh::LoadMeshFile("cube.asciimesh");

	Shader* s = new Shader("BasicVert.glsl", "BasicFrag.glsl", "BasicGeo.glsl");
	Shader* noiseMap = new Shader("blankVert.glsl", "noiseFrag.glsl", "", "NoiseTessEval.glsl", "NoiseTessCont.glsl");

	if (s->UsingDefaultShader()) {
		cout << "Warning: Using default shader! Your shader probably hasn't worked..." << endl;
		cout << "Press any key to continue." << endl;
		std::cin.get();
	}

	cout << s->GetShaderProgram() << endl;

	RenderObject o(m, s);


	//o.SetModelMatrix(Matrix4::Translation(Vector3(0, 0, -10)) * Matrix4::Scale(Vector3(1, 1, 1)));

	float msec = w.GetTimer()->GetTimedMS();
	float rot;
	int vertStore = 1;
	int fragStore = 1;
	int geoStore = 1;
	int tessStore = 1;

	r.AddRenderObject(o);

	r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));

	r.SetViewMatrix(Matrix4::BuildViewMatrix(Vector3(0, 0, 0), Vector3(0, 0, -10)));

	float accumTime = 1.f;
	while (w.UpdateWindow()) {

		msec = w.GetTimer()->GetTimedMS();
		accumTime += msec;

		fragStore = keyboardInputFrag(fragStore);
		vertStore = keyboardInputVert(vertStore);
		geoStore = keyboardInputGeo(geoStore);
		tessStore = keyboardInputGeo(tessStore);
		if (fragStore != keyboardInputFrag(fragStore) || 
			vertStore != keyboardInputVert(vertStore) ||
			geoStore != keyboardInputGeo(geoStore)){
			o.SetShader(changeShader(fragStore, vertStore, geoStore));
		}
		if (geoStore == 2) {
			r.SetProjectionMatrix(Matrix4::Perspective(1.0f, 500.0f, dimensions / dimensions, 45.0f));
		}
		else {
			r.SetProjectionMatrix(Matrix4::Perspective(1, 100, 1.f, 45.0f));
		}
		if (Keyboard::KeyDown(KEY_SPACE) ){
			Mesh * m = Mesh::GenerateQuadPatch();
			Shader * s = new Shader("blankVert.glsl", "noiseFrag.glsl", "",
				"noiseTessCont.glsl", "noiseTessEval.glsl");
			
			 GLuint tex = SOIL_load_OGL_texture("perlinNoise.glsl", SOIL_LOAD_AUTO,
				 SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
			
			 RenderObject o(m, s, tex);
			 o.SetModelMatrix(Matrix4::Scale(Vector3(100, 100, 100)));
		}
	
		else if (tessStore == 2 && Keyboard::KeyTriggered(KEY_1)) {
			o.SetShader(noiseMap);
			tessStore = 1;
		}

		o.SetModelMatrix(
			Matrix4::Translation(Vector3(0, 0, -10)) *
			Matrix4::Rotation(0.1f * accumTime, Vector3(1, 0.8, 0.3))*
			Matrix4::Scale(Vector3(1, 1, 1))
		);
		//this will eventually break due to FP accuracy errors



		r.UpdateScene(msec);
		r.ClearBuffers();
		r.RenderScene();
		r.SwapBuffers();
		//throttle fps
		Sleep(20);
	}
	delete m;
	delete s;
}

