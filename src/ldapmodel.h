/*
  This file is part of libkldap.
  Copyright (c) 2006 Sean Harmer <sh@theharmers.co.uk>

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General  Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; see the file COPYING.LIB.  If not, write to
  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
  Boston, MA 02110-1301, USA.
*/

#ifndef KLDAP_LDAPMODEL_H
#define KLDAP_LDAPMODEL_H

#include <QAbstractItemModel>

#include "ldapconnection.h"
#include "ldapobject.h"
#include "kldap_export.h"

namespace KLDAP {
/**
 * A ModelView interface to an LDAP tree. At present the model is read only. Editing is
 * planned for a future release.
 *
 * This class is best used in conjunction with an LdapStructureProxyModel object for
 * displaying the structure of an LDAP tree, and with LdapAttributeProxyModel for
 * displaying the attributes of particular objects within the tree.
 *
 * \author Sean Harmer <sh@theharmers.co.uk>
 */
class KLDAP_EXPORT LdapModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    enum Roles {
        NodeTypeRole = Qt::UserRole + 1
    };

    enum LdapDataType {
        DistinguishedName = 0,
        Attribute
    };

    /**
     * Constructs an LdapModel. You should set a connection for the model to use with
     * setConnection(). Clients of this class should connect a slot to the ready() signal
     * before setting this model onto a view.
     * @param parent the parent QObject
     * \see setConnection()
     * \see ready()
     */
    explicit LdapModel(QObject *parent = nullptr);
    /**
     * Constructs an LdapModel. Clients of this class should connect a slot to the ready()
     * signal before setting this model onto a view.
     * @param connection the Ldap connection to use in model construction
     * @param parent the parent QObject
     * \see setConnection()
     * \see ready()
     */
    explicit LdapModel(LdapConnection &connection, QObject *parent = nullptr);
    ~LdapModel() override;

    /**
     * Set the connection that the model should use.
     * @param connection the model connection to set
     * \see LdapConnection
     * \see LdapUrl
     */
    void setConnection(LdapConnection &connection);

    //
    // Implement the usual QAbstractItemModel interface
    //
    /**
     * Reimplemented from QAbstractItemModel::index().
     */
    Q_REQUIRED_RESULT QModelIndex index(int row, int col, const QModelIndex &parent) const override;
    /**
     * Reimplemented from QAbstractItemModel::parent().
     */
    Q_REQUIRED_RESULT QModelIndex parent(const QModelIndex &child) const override;
    /**
     * Reimplemented from QAbstractItemModel::data().
     */
    Q_REQUIRED_RESULT QVariant data(const QModelIndex &index, int role) const override;
    /**
     * Reimplemented from QAbstractItemModel::setData(). This is a placeholder for when
     * LdapModel beomes writeable and always returns false.
     */
    Q_REQUIRED_RESULT bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    /**
     * Reimplemented from QAbstractItemModel::headerData().
     */
    Q_REQUIRED_RESULT QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    /**
     * Reimplemented from QAbstractItemModel::flags().
     */
    Q_REQUIRED_RESULT Qt::ItemFlags flags(const QModelIndex &index) const override;
    /**
     * Reimplemented from QAbstractItemModel::columnCount().
     */
    Q_REQUIRED_RESULT int columnCount(const QModelIndex &parent) const override;
    /**
     * Reimplemented from QAbstractItemModel::rowCount().
     */
    Q_REQUIRED_RESULT int rowCount(const QModelIndex &parent) const override;
    /**
     * Reimplemented from QAbstractItemModel::hasChildren().
     */
    Q_REQUIRED_RESULT bool hasChildren(const QModelIndex &parent) const override;
    /**
     * Reimplemented from QAbstractItemModel::canFetchMore().
     */
    Q_REQUIRED_RESULT bool canFetchMore(const QModelIndex &parent) const override;
    /**
     * Reimplemented from QAbstractItemModel::fetchMore().
     */
    void fetchMore(const QModelIndex &parent) override;
    /**
     * Reimplemented from QAbstractItemModel::insertRows(). This is a placeholder for when
     * LdapModel beomes writeable and always returns false.
     */
    Q_REQUIRED_RESULT bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    /**
     * Reimplemented from QAbstractItemModel::removeRows(). This is a placeholder for when
     * LdapModel beomes writeable and always returns false.
     */
    Q_REQUIRED_RESULT bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    /**
     * Reimplemented from QAbstractItemModel::removeRows(). The default implementation
     * does nothing.
     */
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    //
    // Drag and drop support
    //
    /**
     * Reimplemented from QAbstractItemModel::supportedDropActions(). The default
     * implementation returns Qt::MoveAction.
     */
    Q_REQUIRED_RESULT Qt::DropActions supportedDropActions() const override;
    /**
     * Reimplemented from QAbstractItemModel::mimedata(). This is a placeholder for when
     * LdapModel beomes writeable and always returns 0.
     */
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    /**
     * Reimplemented from QAbstractItemModel::dropMimedata(). This is a placeholder for when
     * LdapModel beomes writeable and always returns false.
     */
    Q_REQUIRED_RESULT bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    //
    // Other public utility functions
    //
    /**
     * Checks to see if the item referenced by \p parent has any children of
     * the type \p type. If the item has not been populated by fetchMore() yet,
     * then this function returns true.
     *
     * \see fetchMore()
     * \param parent Index to the item to query.
     * \param type The type of child item to search for.
     */
    bool hasChildrenOfType(const QModelIndex &parent, LdapDataType type) const;

public Q_SLOTS:
    /**
     * Reimplemented from QAbstractItemModel::revert(). This is a placeholder for when
     * LdapModel beomes writeable. This implementation does nothing.
     */
    void revert() override;
    /**
     * Reimplemented from QAbstractItemModel::revert(). This is a placeholder for when
     * LdapModel beomes writeable. This implementation does nothing and returns false.
     */
    bool submit() override;

Q_SIGNALS:
    /**
     * The ready() signal is emitted when the model is ready for use by other components.
     * When the model is first created and a connection is set, the model queries the
     * LDAP server for its base DN and automatically creates items down to that level.
     * This requires the event loop to be running. This signal indicates that this process
     * has completed and the model can now be set onto views or queried directly from code.
     */
    void ready();

private:
    class LdapModelPrivate;
    LdapModelPrivate *const m_d;
};
}
#endif
