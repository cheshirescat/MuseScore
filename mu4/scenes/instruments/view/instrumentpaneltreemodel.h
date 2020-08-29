#ifndef INSTRUMENTPANELTREEMODEL_H
#define INSTRUMENTPANELTREEMODEL_H

#include <QAbstractItemModel>
#include <QItemSelectionModel>
#include <QModelIndex>
#include <QVariant>

#include "abstractinstrumenttreeitem.h"

namespace mu {
namespace scene {
namespace instruments {

class InstrumentPanelTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    Q_PROPERTY(QItemSelectionModel* selectionModel READ selectionModel CONSTANT)
    Q_PROPERTY(bool isMovingUpAvailable READ isMovingUpAvailable WRITE setIsMovingUpAvailable NOTIFY isMovingUpAvailableChanged)
    Q_PROPERTY(bool isMovingDownAvailable READ isMovingDownAvailable WRITE setIsMovingDownAvailable NOTIFY isMovingDownAvailableChanged)
    Q_PROPERTY(bool isRemovingAvailable READ isRemovingAvailable WRITE setIsRemovingAvailable NOTIFY isRemovingAvailableChanged)

public:
    enum RoleNames {
        ItemRole = Qt::UserRole + 1
    };

    explicit InstrumentPanelTreeModel(QObject* parent = nullptr);
    ~InstrumentPanelTreeModel();

    Q_INVOKABLE void selectRow(const QModelIndex& rowIndex, const bool isMultipleSelectionModeOn);
    Q_INVOKABLE void moveSelectedRowsUp();
    Q_INVOKABLE void moveSelectedRowsDown();
    Q_INVOKABLE void removeSelectedRows();

    bool isMovingUpAvailable() const;
    bool isMovingDownAvailable() const;
    bool isRemovingAvailable() const;

    bool removeRows(int row, int count, const QModelIndex& parent) override;
    Q_INVOKABLE bool moveRows(const QModelIndex& sourceParent, int sourceRow, int count, const QModelIndex& destinationParent,
                              int destinationChild) override;

    QModelIndex index(int row, int column, const QModelIndex& parent) const override;
    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent) const override;
    int columnCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    QItemSelectionModel* selectionModel() const;

public slots:
    void setIsMovingUpAvailable(bool isMovingUpAvailable);
    void setIsMovingDownAvailable(bool isMovingDownAvailable);
    void setIsRemovingAvailable(bool isRemovingAvailable);

signals:
    void isMovingUpAvailableChanged(bool isMovingUpAvailable);
    void isMovingDownAvailableChanged(bool isMovingDownAvailable);
    void isRemovingAvailableChanged(bool isRemovingAvailable);

private slots:
    void updateRearrangementAvailability();
    void updateMovingUpAvailability(const bool isSelectionMovable, const QModelIndex& firstSelectedRowIndex = QModelIndex());
    void updateMovingDownAvailability(const bool isSelectionMovable, const QModelIndex& lastSelectedRowIndex = QModelIndex());
    void updateRemovingAvailability();

private:
    AbstractInstrumentTreeItem* m_rootItem = nullptr;
    QItemSelectionModel* m_selectionModel = nullptr;

    bool m_isMovingUpAvailable = false;
    bool m_isMovingDownAvailable = false;
    bool m_isRemovingAvailable = false;
};
}
}
}

#endif // INSTRUMENTPANELTREEMODEL_H
