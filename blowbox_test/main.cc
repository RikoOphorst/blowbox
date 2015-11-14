#include "blowbox/blowbox_include.h"

using namespace blowbox;
using namespace blowbox::direct3d;

int main(int argc, char** argv)
{
	Blowbox* blowbox = Blowbox::Create();

	Window* window = Window::MakeWindow("A blowbox game", 1280, 720);

	Renderer* renderer = Renderer::Create();
	Camera* camera = Camera::Create(BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_PERSPECTIVE);
	
	blowbox->SetWindow(window);
	blowbox->SetRenderer(renderer);

	renderer->SetCamera(camera);
	camera->SetRotation(0.0f, 0.0f, 1.0f);
	camera->TranslateBy(0.0f, 0.0f, -4.0f, BB_CAMERA_TRANSFORMATION_SPACE_LOCAL);

	blowbox->Initialise();

	GameObject* player = GameObject::Create();
	player->SetVertexBuffer(IndexedVertexBuffer::Create(util::ShapeHelper::CreateQuad().vertices, util::ShapeHelper::CreateQuad().indices, util::ShapeHelper::CreateQuad().topology, renderer->GetDevice()));
	player->SetScale({ 50.0f, 50.0f, 50.0f, 1.0f });
	player->SetPosition({ 0.0f, 1.0f, 0.0f, 1.0f });

	blowbox->AddGameObject(player);

	blowbox->Run();

	delete blowbox;

	return 0;
}