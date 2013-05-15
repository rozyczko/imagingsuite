#ifndef IMAGEPAINTER_H
#define IMAGEPAINTER_H
#include <cstdlib>
#include <QPixmap>
#include <QWidget>
#include <QMap>
#include <QColor>
#include <QRect>
#include <QPainter>
#include <map>
#include <logging/logger.h>

class QPainter;


namespace QtAddons {

class ImagePainter
{
    QWidget * m_pParent;
    kipl::logging::Logger logger;
public:
    ImagePainter(QWidget *parent=NULL);
    ~ImagePainter();
    void Render(QPainter &painter, int x, int y, int w, int h);

    void set_image(float const * const data, size_t const * const dims);
    void set_image(float const * const data, size_t const * const dims, const float low, const float high);
    void set_plot(QVector<QPointF> data, QColor color, int idx);
    int clear_plot(int idx=-1);
    void set_rectangle(QRect rect, QColor color, int idx);
    int  clear_rectangle(int idx=-1);

    int  clear();
    void set_levels(const float level_low, const float level_high);
    void get_levels(float *level_low, float *level_high);
    void get_image_minmax(float *level_low, float *level_high);
    void show_clamped(bool show);
    float get_scale() {return m_fScale;}
    int get_offsetX() {return offset_x;}
    int get_offsetY() {return offset_y;}
    //void set_interpolation(Gdk::InterpType interp) {m_Interpolation=interp;}
protected:
    void prepare_pixbuf();

    int m_dims[2];
    int m_NData;

    float m_ImageMin;
    float m_ImageMax;

    float m_MinVal;
    float m_MaxVal;

    float m_WindowScale;
    int offset_x;
    int offset_y;
    int scaled_width;
    int scaled_height;
    float m_fScale;

    //Gdk::InterpType m_Interpolation;
    float * m_data;  //<! float pixel buffer
    uchar * m_cdata;   //<! RGB Pixel buffer

    QMap<int,QPair<QRect, QColor> > m_BoxList;
    QMap<int,QPair<QVector<QPointF>, QColor> > m_PlotList;

    QPixmap m_pixmap_full;
};

}

#endif // IMAGEPAINTER_H
