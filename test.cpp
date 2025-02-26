#include "epframebuffer.h"
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <iostream>

int main(int argc, char **argv){
    DEFAULT_EPFR_CLASS *framebuffer = EPFR_ALLOCATE_NEW;
    QImage artwork("/tmp/art.png");
    QPainter dest(&framebuffer->auxBuffer);
    dest.drawImage(0, 0, artwork);
    framebuffer->swapBuffers(QRect(0, 0, artwork.width(), artwork.height()), Color, QualityFastest, EPFramebuffer::UpdateFlag::CompleteRefresh);
    std::cout << "Buffers swapped" << std::endl;
    framebuffer->sync();
    std::cout << "Sync complate!" << std::endl;

    return 0;
}
