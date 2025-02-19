#include "SpriteRenderer.h"
#include "util/Util.h"
#include "transform.h"
#include "game/Camera.h"

glm::mat4 mat2To4(const glm::mat2& mat2){
    return glm::mat4(
        mat2[0][0], mat2[0][1], 0.0f, 0.0f,  // First row
        mat2[1][0], mat2[1][1], 0.0f, 0.0f,  // Second row
        0.0f,      0.0f,      1.0f, 0.0f,  // Third row
        0.0f,      0.0f,      0.0f, 1.0f   // Fourth row
    );
}

SpriteRenderer::SpriteRenderer(const Shader &shader, const std::vector<float> &vertices)
{
    this->shader = shader;
    this->initRenderData(vertices);
}

SpriteRenderer::~SpriteRenderer()
{
    if(glIsVertexArray(this->quadVAO) == GL_TRUE) {
        glDeleteVertexArrays(1, &this->quadVAO);
        glCheckError();
    }
}
glm::mat4 SpriteRenderer::Transform(glm::vec2 position, glm::vec2 size, float rotate) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    return model;
}
void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::mat4 model, glm::vec3 color, glm::vec2 textureOffset, glm::vec2 textureSize, glm::mat4 view)
{
    Bind();
    // prepare transformations
    this->shader.Use();
    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", Camera::Instance->GetViewMatrix());

    this->shader.SetVector2f("textureOffset", textureOffset);
    this->shader.SetVector2f("textureSize", textureSize);    

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    glCheckError();

    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glCheckError();
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glCheckError();
    glBindVertexArray(0);
    glCheckError();
}
void SpriteRenderer::DrawSprite(const Texture2D &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color, glm::vec2 textureOffset, glm::vec2 textureSize, glm::mat4 view, bool mirror)
{
    Bind();
    // prepare transformations
    this->shader.Use();
    glm::mat4 model = SpriteRenderer::Transform(position, size, rotate);

    // Apply mirroring if needed
    if (mirror) {
        model = glm::scale(model, glm::vec3(-1.0f, 1.0f, 1.0f)); // Mirror horizontally
    }
    this->shader.SetMatrix4("model", model);
    this->shader.SetMatrix4("view", Camera::Instance->GetViewMatrix());

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);
    
    this->shader.SetVector2f("textureOffset", textureOffset);
    this->shader.SetVector2f("textureSize", textureSize);    

    glActiveTexture(GL_TEXTURE0);
    glCheckError();

    texture.Bind();

    glBindVertexArray(this->quadVAO);
    glCheckError();
     glDrawArrays(GL_TRIANGLES, 0, 6);
    glCheckError();
    glBindVertexArray(0);
    glCheckError();
}
void SpriteRenderer::Bind() {
    glBindVertexArray(this->quadVAO);
    glCheckError();
}

void SpriteRenderer::initRenderData(const std::vector<float> &vertices)
{
    // configure VAO/VBO
    unsigned int VBO;

    glGenVertexArrays(1, &this->quadVAO);
    glCheckError();
    glGenBuffers(1, &VBO);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glCheckError();
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glCheckError();

    Bind();
    glEnableVertexAttribArray(0);
    glCheckError();
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glCheckError();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();
    glBindVertexArray(0);
    glCheckError();
}