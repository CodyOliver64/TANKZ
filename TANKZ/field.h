//class BlockC
//{
//public:
//    BlockC();
//    BlockC(float_t leftX, float_t bottomY, float_t rightX, float_t topY, char8_t r, char8_t g, char8_t b);
//    ~BlockC();
//    //bool8_t checkCollision();
//    float_t leftX;
//    float_t rightX;
//    float_t topY;
//    float_t bottomY;
//    char8_t r;
//    char8_t g;
//    char8_t b;
//};

class FieldC : public ObjectC
{
public:
	FieldC(float_t x, float_t y, uint32_t height, uint32_t width, uint32_t initColor);
    ~FieldC();
    void setColor(uint32_t color) {mFieldColor = color;};
    long getColor() {return mFieldColor;};
    void update(DWORD milliseconds);
    virtual void render();
    void setWidth(uint32_t width) {mWidth = width;};
    uint32_t getWidth() {return mWidth;};
    void setHeight(uint32_t height) {mHeight = height;};
    uint32_t getHeight() {return mHeight;};

    //BlockC blocks[8];

	void moveUp();
private:
    uint32_t mFieldColor;
	uint32_t mHeight;
	uint32_t mWidth;
	bool8_t mEnabled;
    uint32_t numBlocks;
};