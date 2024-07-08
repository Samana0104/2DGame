// �ȼ����̴� , float1(x), float2(x,y), float3(x,y,z), float4(x,y,z,w)
// ��ȯ�� = FLOAT4(R,G,B,A)�� ��ȯ�Ǿ�� �Ѵ�.
// �ø�ƽ(�ṉ̀���) : SV_POSITION, SV_TARGET
// ���̴� �Է� �� ��� �����ʹ� 
// ������ �������Ϳ� ���� �� ��� �Ǿ�� �Ѵ�.

Texture2D g_txTexture : register(t0);
SamplerState sampler0 : register(s0);

struct PS_In
{
	float4 p : SV_POSITION;// �ݵ�� float4
	float4 c  :COLOR;
	float2 t  :TEXCOORD0;
    float2 v : VPOS;
};

struct PS_Out
{
	float4 c : SV_Target;
};

PS_Out PSMain( PS_In psIn )
{
	PS_Out  psOut=(PS_Out)0;
	float4 pixel = g_txTexture.Sample(sampler0, psIn.t);

    if (pixel.r == 1.f && pixel.g == 0.f && pixel.b == 1.f)
        discard;
	
    if (pixel.r == 0.f && pixel.g == 1.f && pixel.b == 1.f)
        discard;

    psOut.c = pixel * psIn.c;
	//psOut.c = pixel;

     if (psOut.c.r <= 0.1f)
    {
        psOut.c.rgb *= 4.f;
    }
    else if (psOut.c.r <= 0.3f)  // threshhold
    {
        psOut.c.rgb *= 2.5f;
    }
    else
    {
        psOut.c.rgb *= 1.5f;
    }
	

	return psOut;
  //return float4(psIn.t.x, psIn.t.y, 0,1);
}