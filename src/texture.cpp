#include <nori/texture.h>
#include <QFile>

#include "pfm.h"
NORI_NAMESPACE_BEGIN
class UvTexture: public Texture {
public:
	UvTexture( const PropertyList &propList):m_data(NULL) {
		m_filename = propList.getString("filename");
		std::string filename = m_filename.toStdString();
		m_channel = ReadPfm(filename.c_str(), m_width, m_height, m_data);
		if (m_channel<=0) {
			throw NoriException(QString("UvTexture: Cannot open \"%1\"").arg(m_filename));
		}
	}
	Color3f lookUp(float u, float v) const;
	QString toString() const {
		return QString("Texture[type=uv]");
	}
	const Color3f texel(int u, int v) const{
		 u = clamp(u, 0, m_width - 1);
         v = clamp(v, 0, m_height - 1);
		 int start = (v*m_width+u)*m_channel;
		 assert( start + 2 < m_width*m_height*m_channel );
		 return Color3f(
			 m_data[start],
			 m_data[start+1], 
			 m_data[start+2]
			 );
	}
	virtual ~UvTexture(){
		delete m_data;
	}
private:
	float* m_data;
	int m_width;
	int m_height;
	int m_channel;
	QString m_filename;
};

Color3f UvTexture::lookUp(float u, float v) const {
	u = u*m_width - 0.5f;
	v = v*m_height - 0.5f;
	int u0 = std::floor(u);
	int v0 = std::floor(v);
	float du = u-u0, dv = v-v0;
	return (1.0f-du)*(1.0f-dv)*texel(u0, v0) +
		   (1.0f-du)*dv       *texel(u0, v0+1) +
		   du       *(1.0f-dv)*texel(u0+1, v0) +
		   du       *dv       *texel(u0+1, v0+1);
}

NORI_REGISTER_CLASS(UvTexture, "uv");
NORI_NAMESPACE_END