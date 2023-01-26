#ifndef JGEOMETRY_H
#define JGEOMETRY_H

#include "types.h"
#include "JSystem/JMath/JMath.h"

// from SMS decomp
namespace JGeometry
{
    // placeholders
    template <typename T>
    struct TUtil
    {

    };
    template <>
    struct TUtil<f32> {
        f32 atan2(f32 y, f32 x) { return JMAAtan2Radian(y, x); };
    };

    template <typename T>
    struct TVec2
    {
        TVec2() {}
        TVec2(T x, T y) { set(x, y); }

        void set(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        void set(const TVec2 &other)
        {
            x = other.x;
            y = other.y;
        }

        void setMin(const TVec2<f32> &min)
        {
            if (x >= min.x)
                x = min.x;
            if (y >= min.y)
                y = min.y;
        }

        void setMax(const TVec2<f32> &max)
        {
            if (x <= max.x)
                x = max.x;
            if (y <= max.y)
                y = max.y;
        }

        void add(const TVec2<T> &other)
        {
            x += other.x;
            y += other.y;
        }

        /** @fabricated */
        // TVec2<T> adding(const TVec2<T>& other) { return TVec2<T>(x + other.x, y + other.y); }

        bool isAbove(const TVec2<T> &other) const { return (x >= other.x) && (y >= other.y) ? true : false; }

        T x;
        T y;
    };

    template <typename T>
    class TVec3
    {
    public:
        TVec3();
        TVec3(const TVec3 &);

        template <typename TY>
        TVec3(TY, TY, TY);

        TVec3 &operator=(const TVec3 &);
        TVec3 &operator*=(const TVec3 &operand);
        TVec3 &operator-=(const TVec3 &operand);

        void add(const TVec3 &operand);
        void div(f32 divisor);
        f32 dot(const TVec3 &operand) const;
        f32 length() const;
        void negate();
        f32 normalize();
        void scale(f32 scale);
        void scale(f32 scale, const TVec3 &operand);
        void scaleAdd(f32 scale, const TVec3 &operand, const TVec3 &translate);

        template <typename TY>
        void set(TY X, TY Y, TY Z) {
            x = X;
            y = Y;
            z = Z;
        }
        
        template <typename TY>
        void set(const TVec3<TY> &src)
        {
            x = src.x;
            y = src.y;
            z = src.z;
        }

        void setLength(const TVec3 &operand, f32 length);
        void setMax(const TVec3 &other);
        void setMin(const TVec3 &other);
        void sub(const TVec3<T> &translate)
        { // i'm bad coder please implement correctly
            JMathInlineVEC::PSVECSubtract(reinterpret_cast<const Vec *>(this), reinterpret_cast<const Vec *>(&translate), reinterpret_cast<Vec *>(this));
        }
        void sub(const TVec3 &base, const TVec3 &translate);

        void zero(); /*{
            x = 0;
            y = 0;
            z = 0;
        }*/

        T x;
        T y;
        T z;
    };

    // Size: 0x10
    template <class T>
    struct TBox
    {
        TBox()
            : i(), f()
        {
        }
        TBox(const TBox &other)
            : i(other.f), f(other.y)
        {
        }

        T i, f;
    };

    // clang-format off
template<> struct TBox<TVec2<f32> > {
    f32 getWidth() const { return f.x - i.x; }
    f32 getHeight() const { return f.y - i.y; }

    bool isValid() const { return f.isAbove(i); }

    void addPos(f32 x, f32 y) {
        addPos(TVec2<f32>(x, y));
    }

    void addPos(const TVec2<f32>& pos) {
        i.add(pos);
        f.add(pos);
    }

    bool intersect(const TBox<TVec2<f32> >& other) {
        i.setMax(other.i);
        f.setMin(other.f);
        return isValid();
    }

    TVec2<f32> i, f;
};

template <typename T>
struct TBox2 : TBox<TVec2<T> > {
    TBox2() {}
    TBox2(const TVec2<f32>& i, const TVec2<f32> f) { set(i, f); }
    TBox2(f32 x0, f32 y0, f32 x1, f32 y1) { set(x0, y0, x1, y1); }
	TBox2(f32 x0, f32 y0, TVec2<f32>& f) { set(x0, y0, x0 + f.x, y0 + f.y);	}
	TBox2(f32 val)
	{
		f.y = val;
		f.x = val;
		i.y = val;
		i.x = val;
	}

    void absolute() {
        if (!this->isValid()) {
            TBox2<T> box(*this);
            this->i.setMin(box.i);
            this->i.setMin(box.f);
            this->f.setMax(box.i);
            this->f.setMax(box.f);
        }
    }

	// /** @fabricated */
	// TBox2<T>& addingPos(TBox2<T>& result, const TVec2<T>& pos) {
	// 	return TBox2<T>(i.adding(pos), f.adding(pos));
	// }

    void set(const TBox2& other) { set(other.i, other.f); }
    void set(const TVec2<f32>& i, const TVec2<f32>& f) { this->i.set(i), this->f.set(f); }
    void set(f32 x0, f32 y0, f32 x1, f32 y1) { i.set(x0, y0); f.set(x1, y1); }
};

    // clang-format on

    template <typename T>
    struct TBox3
    {
        T minX;
        T minY;
        T minZ;
        T maxX;
        T maxY;
        T maxZ;
    };

    typedef TVec2<float> TVec2f;
    typedef TVec3<float> TVec3f;
    typedef TBox2<float> TBox2f;
    typedef TBox3<float> TBox3f;
};

#endif