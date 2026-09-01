#pragma once
#include <QImage>
#include <QRect>
#include <QFlags>
#include <vector>


enum class EPScreenMode {
    Pen = 0,
    Mono = 1,
    Animation = 2,
    UI = 3,
    Content = 4,
    Sleep = 5,
};

class EPScreenModeMap {
    struct Translation{}; // what's that?
public:
    QRegion modeRegions[6];
    char OPAQUE[0x58 - sizeof(QRegion) * 6];
    EPScreenModeMap(QSize size, std::vector<EPScreenModeMap::Translation> &&pval);
    void setModeForRegion(const QRegion &reg, EPScreenMode mode);
    bool isOnly(int mode) const;
    void dump() const;


    static inline EPScreenModeMap *createAsInXochitl() { 
        return new EPScreenModeMap(QSize(-1, -1), std::vector<Translation>());
    }
};


static_assert(sizeof(struct EPScreenModeMap) == 0x58, "Wrong size");

class EPFramebuffer {
public:
    enum UpdateFlag {
        NoFullRefresh = 0,
        CompleteRefresh = 1,
    };
    unsigned long swapBuffers(QRect rect, EPScreenMode type, QFlags<EPFramebuffer::UpdateFlag> flags);
    unsigned long swapBuffers(const QRegion &region, const EPScreenModeMap &mode, QFlags<EPFramebuffer::UpdateFlag> flags);
    #ifdef EPFB_INTERNAL
    static EPFramebuffer *instance();
    #endif
    static EPFramebuffer *createControlledInstance();

    // Injected:
    QImage *getAuxFramebuffer();
    QImage *getMainFramebuffer();
};
