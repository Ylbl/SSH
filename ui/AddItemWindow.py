# Form implementation generated from reading ui file 'F:\qt_test\SSH\ui\AddItemWindow.ui'
#
# Created by: PyQt6 UI code generator 6.8.1
#
# WARNING: Any manual changes made to this file will be lost when pyuic6 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt6 import QtCore, QtGui, QtWidgets


class Ui_AddItemWindow(object):
    def setupUi(self, AddItemWindow):
        AddItemWindow.setObjectName("AddItemWindow")
        AddItemWindow.resize(971, 718)
        self.horizontalLayout_3 = QtWidgets.QHBoxLayout(AddItemWindow)
        self.horizontalLayout_3.setObjectName("horizontalLayout_3")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout()
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.horizontalLayout = QtWidgets.QHBoxLayout()
        self.horizontalLayout.setObjectName("horizontalLayout")
        self.label = QtWidgets.QLabel(parent=AddItemWindow)
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.horizontalLayout.addWidget(self.label)
        self.sourceInput = QtWidgets.QLineEdit(parent=AddItemWindow)
        self.sourceInput.setObjectName("sourceInput")
        self.horizontalLayout.addWidget(self.sourceInput)
        self.verticalLayout_2.addLayout(self.horizontalLayout)
        self.verticalLayout = QtWidgets.QVBoxLayout()
        self.verticalLayout.setObjectName("verticalLayout")
        self.label_2 = QtWidgets.QLabel(parent=AddItemWindow)
        font = QtGui.QFont()
        font.setPointSize(16)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.verticalLayout.addWidget(self.label_2)
        self.descriptionInput = QtWidgets.QTextEdit(parent=AddItemWindow)
        self.descriptionInput.setObjectName("descriptionInput")
        self.verticalLayout.addWidget(self.descriptionInput)
        self.verticalLayout_2.addLayout(self.verticalLayout)
        self.horizontalLayout_2 = QtWidgets.QHBoxLayout()
        self.horizontalLayout_2.setObjectName("horizontalLayout_2")
        self.pushButton = QtWidgets.QPushButton(parent=AddItemWindow)
        self.pushButton.setMinimumSize(QtCore.QSize(0, 30))
        self.pushButton.setObjectName("pushButton")
        self.horizontalLayout_2.addWidget(self.pushButton)
        self.pushButton_2 = QtWidgets.QPushButton(parent=AddItemWindow)
        self.pushButton_2.setMinimumSize(QtCore.QSize(0, 30))
        self.pushButton_2.setObjectName("pushButton_2")
        self.horizontalLayout_2.addWidget(self.pushButton_2)
        self.pushButton_3 = QtWidgets.QPushButton(parent=AddItemWindow)
        self.pushButton_3.setMinimumSize(QtCore.QSize(0, 30))
        self.pushButton_3.setObjectName("pushButton_3")
        self.horizontalLayout_2.addWidget(self.pushButton_3)
        self.verticalLayout_2.addLayout(self.horizontalLayout_2)
        self.horizontalLayout_3.addLayout(self.verticalLayout_2)
        spacerItem = QtWidgets.QSpacerItem(1, 20, QtWidgets.QSizePolicy.Policy.Expanding, QtWidgets.QSizePolicy.Policy.Minimum)
        self.horizontalLayout_3.addItem(spacerItem)
        self.widget = QtWidgets.QWidget(parent=AddItemWindow)
        self.widget.setMinimumSize(QtCore.QSize(700, 700))
        self.widget.setObjectName("widget")
        self.gridLayout = QtWidgets.QGridLayout(self.widget)
        self.gridLayout.setObjectName("gridLayout")
        self.video = QtWidgets.QLabel(parent=self.widget)
        self.video.setText("")
        self.video.setObjectName("video")
        self.gridLayout.addWidget(self.video, 0, 0, 1, 1)
        self.horizontalLayout_3.addWidget(self.widget)

        self.retranslateUi(AddItemWindow)
        self.pushButton_3.clicked.connect(AddItemWindow.captureBC) # type: ignore
        self.pushButton.clicked.connect(AddItemWindow.confirmBC) # type: ignore
        QtCore.QMetaObject.connectSlotsByName(AddItemWindow)

    def retranslateUi(self, AddItemWindow):
        _translate = QtCore.QCoreApplication.translate
        AddItemWindow.setWindowTitle(_translate("AddItemWindow", "Form"))
        self.label.setText(_translate("AddItemWindow", "来源"))
        self.label_2.setText(_translate("AddItemWindow", "描述/备注"))
        self.pushButton.setText(_translate("AddItemWindow", "确定"))
        self.pushButton_2.setText(_translate("AddItemWindow", "取消"))
        self.pushButton_3.setText(_translate("AddItemWindow", "截取并选择"))
