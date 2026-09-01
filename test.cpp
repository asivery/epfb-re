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

    // OLD Api:
    framebuffer->swapBuffers(QRect(0, 0, artwork.width(), artwork.height()), EPScreenMode::Sleep, EPFramebuffer::UpdateFlag::CompleteRefresh);

    // NEW Api:
    // EPScreenModeMap *map = EPScreenModeMap::createAsInXochitl();
    // map->dump();
    // map->setModeForRegion(QRegion(0, 0, 100, artwork.height()), EPScreenMode::Sleep);
    // map->dump();
    // framebuffer->swapBuffers(QRegion(0, 0, 100, artwork.height()), *map, EPFramebuffer::UpdateFlag::NoFullRefresh);
    // delete map;

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
