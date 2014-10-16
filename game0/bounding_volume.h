#ifndef BOUNDING_VOLUME_H
#define BOUNDING_VOLUME_H

class BoundingVolume
{
public:
    BoundingVolume();

    void save();
    void remove();
    static BoundingVolume* load(int id);

    float width() const {
        return m_width;
    }

    float height() const {
        return m_height;
    }

    float depth() const {
        return m_depth;
    }

    void setWidth(float value) {
        m_width = value;
    }

    void setHeight(float value) {
        m_height = value;
    }

    void setDepth(float value) {
        m_depth = value;
    }

    int id() const {
        return m_id;
    }

private:
    int m_id{-1};
    float m_width{0};
    float m_height{0};
    float m_depth{0};
};

#endif // BOUNDING_VOLUME_H
