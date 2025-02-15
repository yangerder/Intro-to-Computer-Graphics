#version 330 core

layout(triangles) in; // 幾何著色器接收三角形作為輸入
layout(triangle_strip, max_vertices = 3) out; // 輸出三角形條帶

in vec2 TexCoord[]; // 從頂點著色器接收到的每個頂點的 TexCoord
out vec2 fragTexCoord; // 傳遞給片段著色器的 TexCoord

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time; // 動態時間
uniform vec3 explosionCenter; // 爆炸中心點

void main()
{
    for (int i = 0; i < 3; i++) {
        // 計算頂點到爆炸中心的方向
        vec3 direction = gl_in[i].gl_Position.xyz - explosionCenter;

        // 動態增加偏移，根據時間放大
        vec3 explodedPosition = gl_in[i].gl_Position.xyz + normalize(direction) * time * 5.0;

        // 設置輸出頂點位置
        gl_Position = projection * view * model * vec4(explodedPosition, 1.0);

        // 傳遞紋理坐標給片段著色器
        fragTexCoord = TexCoord[i];

        EmitVertex(); // 發出頂點
    }
    EndPrimitive(); // 結束一個圖元
}
