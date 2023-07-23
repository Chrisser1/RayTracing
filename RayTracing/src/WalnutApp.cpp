#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Timer.h"
#include "Walnut/Random.h"

#include "Renderer.h"
#include "Camera.h"

#include <glm/gtc/type_ptr.hpp>

using namespace Walnut;

class ExampleLayer : public Walnut::Layer
{
public:
	void RandomScene()
	{
		// Ground
		Material& groundMaterial = m_Scene.Materials.emplace_back(); // index 0
		groundMaterial.Albedo = { 1.0f, 0.0f, 1.0f };
		groundMaterial.Roughness = 1.0f;

		{
			Sphere sphere;
			sphere.Position = { 0.0f, -1000.0f, 0.0f };
			sphere.Radius = 1000.0f;
			sphere.MaterialIndex = 0;
			m_Scene.Spheres.push_back(sphere);
		}

		// Sun
		Material& Sun = m_Scene.Materials.emplace_back(); // index 0
		Sun.Roughness = 1.0f;
		Sun.EmissionColor = { 0.3f, 0.5f, 0.6f };
		Sun.EmissionPower = 2.0f;

		{
			Sphere sphere;
			sphere.Position = { 0.0f, 120.0f, -100.0f };
			sphere.Radius = 100.0f;
			sphere.MaterialIndex = 1;
			m_Scene.Spheres.push_back(sphere);
		}

		// Red
		Material& redSphere = m_Scene.Materials.emplace_back();
		redSphere.Albedo = { 1.0f, 0.0f, 0.0f };
		redSphere.Roughness = 0.5f;

		{
			Sphere sphere;
			sphere.Position = { 0.0f, 1.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.MaterialIndex = 2;
			m_Scene.Spheres.push_back(sphere);
		}

		// Green
		Material& greenSphere = m_Scene.Materials.emplace_back();
		greenSphere.Albedo = { 0.0f, 1.0f, 0.0f };
		greenSphere.Roughness = 0.5f;

		{
			Sphere sphere;
			sphere.Position = { -4.0f, 1.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.MaterialIndex = 3;
			m_Scene.Spheres.push_back(sphere);
		}

		// Blue
		Material& blueSphere = m_Scene.Materials.emplace_back();
		blueSphere.Albedo = { 0.0f, 0.0f, 1.0f };
		blueSphere.Roughness = 0.5f;

		{
			Sphere sphere;
			sphere.Position = { 4.0f, 1.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.MaterialIndex = 4;
			m_Scene.Spheres.push_back(sphere);
		}

		for (int a = -1; a < 1; a++)
		{
			for (int b = -1; b < 1; b++)
			{
				float chooseMat = Walnut::Random::Float();
				glm::vec3 center((float)a + 0.9f * Walnut::Random::Float(), 0.2f, (float)b + 0.9f * Walnut::Random::Float());

				if ((center - glm::vec3(4.0f, 0.2f, 0.0f)).length() > 0.9f)
				{
					Material& sphereMaterial = m_Scene.Materials.emplace_back();

					if (chooseMat < 0.8) {
						// difuse
						sphereMaterial.Albedo = glm::vec3(Walnut::Random::Float(), Walnut::Random::Float(), Walnut::Random::Float());
						sphereMaterial.Roughness = 1.0f;

						Sphere sphere;
						sphere.Position = center;
						sphere.Radius = 0.2f;
						sphere.MaterialIndex = (int)m_Scene.Materials.size();
						m_Scene.Spheres.push_back(sphere);
					}
					else if (chooseMat < 0.95f)
					{
						// Metal
						sphereMaterial.Albedo = glm::vec3(Walnut::Random::Float(), Walnut::Random::Float(), Walnut::Random::Float());
						sphereMaterial.Roughness = Walnut::Random::Float();
						sphereMaterial.Metallic = Walnut::Random::Float();

						Sphere sphere;
						sphere.Position = center;
						sphere.Radius = 0.2f;
						sphere.MaterialIndex = (int)m_Scene.Materials.size();
						m_Scene.Spheres.push_back(sphere);
					}
					else
					{
						// difuse : Should be glass
						sphereMaterial.Albedo = glm::vec3(Walnut::Random::Float(), Walnut::Random::Float(), Walnut::Random::Float());
						sphereMaterial.Roughness = 1.0f;

						Sphere sphere;
						center.y += 0.3f;
						sphere.Position = center;
						sphere.Radius = 0.2f + 0.3f;
						sphere.MaterialIndex = (int)m_Scene.Materials.size();
						m_Scene.Spheres.push_back(sphere);
					}
				}
			}
		}
	}

	ExampleLayer()
		: m_Camera(45.0f, 0.1f, 100.0f) 
	{
		/*Material& pinkSphere = m_Scene.Materials.emplace_back();
		pinkSphere.Albedo = { 1.0f, 0.0f, 1.0f };
		pinkSphere.Roughness = 0.0f;


		Material& blueSphere = m_Scene.Materials.emplace_back();
		blueSphere.Albedo = { 0.2f, 0.3f, 1.0f };
		blueSphere.Roughness = 0.1f;

		Material& orangeSphere = m_Scene.Materials.emplace_back();
		orangeSphere.Albedo = { 0.8f, 0.5f, 0.2f };
		orangeSphere.Roughness = 0.1f;
		orangeSphere.EmissionColor = orangeSphere.Albedo;
		orangeSphere.EmissionPower = 2.0f;

		{
			Sphere sphere;
			sphere.Position = { 0.0f, 0.0f, 0.0f };
			sphere.Radius = 1.0f;
			sphere.MaterialIndex = 0;
			m_Scene.Spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Position = { 1.0f, -101.0f, 0.0f };
			sphere.Radius = 100.0f;
			sphere.MaterialIndex = 1;
			m_Scene.Spheres.push_back(sphere);
		}

		{
			Sphere sphere;
			sphere.Position = { 2.0f, 100.0f, -105.0f };
			sphere.Radius = 100.0f;
			sphere.MaterialIndex = 2;
			m_Scene.Spheres.push_back(sphere);
		}*/

		RandomScene();
	}

	virtual void OnUpdate(float ts) override
	{
		if (m_Camera.OnUpdate(ts))
			m_Renderer.ResetFrameIndex();
	}

	virtual void OnUIRender() override
	{
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render"))
		{
			Render();
		}

		ImGui::Checkbox("Accumulata", &m_Renderer.GetSettings().Accumulate);

		if (ImGui::Button("Reset"))
		{
			m_Renderer.ResetFrameIndex();
		}

		ImGui::End();

		ImGui::Begin("Scene");
		for (size_t i = 0; i < m_Scene.Spheres.size(); i++)
		{
			ImGui::PushID(i);

			Sphere& sphere = m_Scene.Spheres[i];
			ImGui::DragFloat3("Position", glm::value_ptr(sphere.Position), 0.1f);
			ImGui::DragFloat("Radius", &sphere.Radius, 0.1f);
			ImGui::DragInt("Material", &sphere.MaterialIndex, 1.0f, 0, (int)m_Scene.Materials.size() - 1);

			ImGui::Separator();
			ImGui::PopID();
		}

		for (size_t i = 0; i < m_Scene.Materials.size(); i++)
		{
			ImGui::PushID(i);

			Material& material = m_Scene.Materials[i];
			ImGui::ColorEdit3("Albedo", glm::value_ptr(material.Albedo), 0.1f);
			ImGui::DragFloat("Roughness", &material.Roughness, 0.001f, 0.0f, 1.0f);
			ImGui::DragFloat("Metallic", &material.Metallic, 0.001f, 0.0f, 1.0f);
			ImGui::ColorEdit3("Emission Color", glm::value_ptr(material.EmissionColor), 0.1f);
			ImGui::DragFloat("Emission Power", &material.EmissionPower, 0.001f, 0.0f, FLT_MAX);

			ImGui::Separator();
			ImGui::PopID();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("Viewport");

		m_ViewportWidth = ImGui::GetContentRegionAvail().x;
		m_ViewportHeight = ImGui::GetContentRegionAvail().y;

		auto image = m_Renderer.GetFinalImage();
		if (image)
			ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(), (float)image->GetHeight() },
				ImVec2(0, 1), ImVec2(1, 0));

		ImGui::End();
		ImGui::PopStyleVar();

		Render();
	}

	void Render()
	{
		Timer timer;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Camera.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render(m_Scene, m_Camera);

		m_LastRenderTime = timer.ElapsedMillis();
	}
private:
	Renderer m_Renderer;
	Camera m_Camera;
	Scene m_Scene;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;

	float m_LastRenderTime = 0.0f;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Ray Tracing";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});
	return app;
}