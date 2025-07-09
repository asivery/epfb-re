#include "epframebuffer.h"
#include <QImage>
#include <QPainter>
#include <QRect>
#include <QTimer>
#include <QCoreApplication>
#include <iostream>

void run(){
    EPFramebuffer *framebuffer = EPFramebuffer::createControlledInstance();
    QImage artwork("/tmp/art.png");
    QPainter dest(framebuffer->getAuxFramebuffer());
    dest.drawImage(0, 0, artwork);
    framebuffer->swapBuffers(QRect(0, 0, artwork.width(), artwork.height()), Color, QualityFastest, EPFramebuffer::UpdateFlag::CompleteRefresh);
    std::cout << "Buffers swapped" << std::endl;
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QTimer::singleShot(0, []() {
        // EPFramebuffer wants to run in QT context
        // and I don't want to mess up the screen
        // so let's give it what it wants:
        run();
        QCoreApplication::quit();
    });

    return app.exec();
}
