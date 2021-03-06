/*
 * (c) 2019 Gustavo Valiente gustavo.valiente@protonmail.com
 *
 * MIT License, see LICENSE file.
 */

#include "pcps_vw_normal_split_cloud_widget.h"

#include "Q3DObserver"
#include "pcps_vw_result.h"
#include "pcps_vw_random.h"

namespace pcps
{
namespace vw
{

QString NormalSplitCloudWidget::_updateViewer(const PointCloud*, const Result* result, Q3DObserver& viewer)
{
    QString text;

    if(result)
    {
        Random random;
        const std::vector<NormalRegion>& normalRegions = result->normalSplitResult;
        const Cloud& cloud = result->organizationResult;
        const std::vector<Point>& points = cloud.points;
        const Point* pointsData = points.data();
        auto numPoints = int(points.size());
        int cloudWidth = cloud.width;
        viewer.reservePoints(numPoints);

        for(const NormalRegion& normalRegion : normalRegions)
        {
            QColor color(64 + (random.get() % 128), 64 + (random.get() % 128), 64 + (random.get() % 128));
            int xi = normalRegion.x;
            int xl = normalRegion.x + normalRegion.width;
            int yi = normalRegion.y;
            int yl = normalRegion.y + normalRegion.height;

            for(int y = yi; y < yl; ++y)
            {
                const Point* pointsRow = pointsData + (y * cloudWidth);

                for(int x = xi; x < xl; ++x)
                {
                    const Point& point = pointsRow[x];

                    if(point.isFinite())
                    {
                        viewer.addPoint(QVector3D(point.x, point.y, point.z), color);
                    }
                }
            }
        }

        text += "Normal regions: ";
        text += QString::number(normalRegions.size());
        text += "\nElapsed microseconds: ";
        text += QString::number(result->normalSplitElapsedMcs);
    }

    return text;
}

}
}
