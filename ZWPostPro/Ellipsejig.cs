//
//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////

using System;
using ZwSoft.ZwCAD.DatabaseServices;
using ZwSoft.ZwCAD.Runtime;
using ZwSoft.ZwCAD.Geometry;
using ZwSoft.ZwCAD.ApplicationServices;
using System.Reflection;

using System.IO;
using System.Collections;
using System.Runtime.InteropServices;
using System.Diagnostics;
using ZwSoft.ZwCAD.EditorInput;
using ZwSoft.ZwCAD.GraphicsInterface;

using JigSample;

/*
 *安装步骤：
 *01.修改C:\Program Files (x86)\ZWCAD+ 2014\Support\ZWCAD2014.lsp 自动加载--修改方式如下文介绍
 *   ZwManaged.dll ZwDatabaseMgd.dll JigSample.dll 拷贝到D:\TYuan目录下
 *02.D:\TYuan\DIMTemplate.dwg存放模板文件
 *03.需要有D盘根目录 存放文件 save这个函数不工作
 
 * *04.开发注意：一定不能引用错了ZwManaged.dll ZwDatabaseMgd.dll  否则各种莫名其妙的错误
 */
//自动加载办法
//修改文件
//C:\Program Files (x86)\ZWCAD+ 2014\Support\ZWCAD2014.lsp
//添加一行
/*
(vl-load-com)

(load "ZWCAD2014doc.lsp")
(command "netload" "D:\\TYuan\\JigSample.dll")
(princ)

 */
[assembly: CommandClass(typeof(JigSample.TestEntityJig))]


//This application implements a command called ellipsejig. It will help you 
//create an ellipse from scratch by doing a jig. The user is first asked to
//enter the ellipse major axis followed by ellipse minor axis. 

//To use ellipsejig.dll:
//1. Start AutoCAD and open a new drawing.
//2. Type netload and select ellipsejig.dll.
//3. Execute the ellipsejig command, defined by ellipsejig.dll.

//Please add the References acdbmgd.dll,acmgd.dll,
//ZwSoft.ZwCAD.Interop.dll and ZwSoft.ZwCAD.Interop.Common.dll
//before trying to build this project.

namespace JigSample
{
	public static class TestEntityJig 
	{
		[CommandMethod("wt1")]
		static public void DoIt()
        {
            string[] files = Class1.GetFiles();
            foreach (string fileName in files)
            {
                ReadDwgFileTest(fileName);
            }

            Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            ed.WriteMessage("\n工作结束.");
            return;

            Database database = HostApplicationServices.WorkingDatabase;
            using (Transaction transaction = database.TransactionManager.StartTransaction())
            {
                BlockTableRecord btRecord = (BlockTableRecord)transaction.GetObject(SymbolUtilityServices.GetBlockModelSpaceId(database), OpenMode.ForRead);

                foreach (ObjectId id in btRecord)
                {
                    Entity entity = (Entity)transaction.GetObject(id, OpenMode.ForWrite);
                    entity.LinetypeScale = 0.1;
                    entity.Dispose();
                    //Access to the entity
                    //MgdAcApplication.DocumentManager.MdiActiveDocument.Editor.WriteMessage(string.Format("\nHandle: {0}", entity.Handle));
                }
                transaction.Commit();
            }
            database.Dispose();
            return;





            /*foreach (ObjectId id in btr)
              {
                  Entity ent = trans.GetObject(id, OpenMode.ForWrite) as Entity;
                  ent.LinetypeScale = 0.1;
                  ent.Dispose();
              }*/



            return;

            /*Database db1 = HostApplicationServices.WorkingDatabase;

            //ObjectId model = db1.CurrentSpaceId;//模型空间的Id

            using (Transaction trans = db1.TransactionManager.StartTransaction())
            {

                //BlockTable bt = (BlockTable)trans.GetObject(db1.BlockTableId, OpenMode.ForRead);
                //打开数据库的模型空间块表记录对象
                BlockTableRecord btr = (BlockTableRecord)trans.GetObject(db1.CurrentSpaceId, OpenMode.ForWrite);

                //btr.GetEnumerator();
                //循环遍历模型空间中的实体
     

                trans.Commit();
            }
            db1.Dispose();*/

            return;



            /*Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            //ImportBlocksFromDwg(this Database destDb, string sourceFileName);
            Database db = HostApplicationServices.WorkingDatabase;
            ImportBlocksFromDwg(db, "D:\\TYuan\\DIMTemplate.dwg");
            db.Dispose();*/

            return;

            /*string[] files = Class1.GetFiles();
            foreach (string fileName in files)
            {
                OpenDwg(fileName);
            }*/
           
            
		}


        public static ObjectId InsertBlockReference(this ObjectId spaceId, string layer, string blockName, Point3d position, Scale3d scale, double rotateAngle)
        {
            ObjectId blockRefId;//存储要插入的块参照的Id
            Database db = spaceId.Database;//获取数据库对象
            //以读的方式打开块表
            BlockTable bt = (BlockTable)db.BlockTableId.GetObject(OpenMode.ForRead);
            //如果没有blockName表示的块，则程序返回
            if (!bt.Has(blockName)) return ObjectId.Null;
            //以写的方式打开空间（模型空间或图纸空间）
            BlockTableRecord space = (BlockTableRecord)spaceId.GetObject(OpenMode.ForWrite);
            //创建一个块参照并设置插入点
            BlockReference br = new BlockReference(position, bt[blockName]);
            br.ScaleFactors = scale;//设置块参照的缩放比例
            br.Layer = layer;//设置块参照的层名
            br.Rotation = rotateAngle;//设置块参照的旋转角度
            ObjectId btrId = bt[blockName];//获取块表记录的Id
            //打开块表记录
            BlockTableRecord record = (BlockTableRecord)btrId.GetObject(OpenMode.ForRead);
            //添加可缩放性支持
            //if (record.Annotative == AnnotativeStates.True)
            {
                //ObjectContextCollection contextCollection = db.ObjectContextManager.GetContextCollection("ACDB_ANNOTATIONSCALES");
                //ObjectContexts.AddContext(br, contextCollection.GetContext("1:1"));
            }
            blockRefId = space.AppendEntity(br);//在空间中加入创建的块参照
            db.TransactionManager.AddNewlyCreatedDBObject(br, true);//通知事务处理加入创建的块参照
            space.DowngradeOpen();//为了安全，将块表状态改为读
            return blockRefId;//返回添加的块参照的Id
        }

        public static void ImportBlocksFromDwg(this Database destDb, string sourceFileName)
        {
            //创建一个新的数据库对象，作为源数据库，以读入外部文件中的对象
            Database sourceDb = new Database(false, true);
            try
            {
                //把DWG文件读入到一个临时的数据库中
                sourceDb.ReadDwgFile(sourceFileName, System.IO.FileShare.Read, true, null);
                //创建一个变量用来存储块的ObjectId列表
                ObjectIdCollection blockIds = new ObjectIdCollection();
                //获取源数据库的事务处理管理器
                ZwSoft.ZwCAD.DatabaseServices.TransactionManager tm = sourceDb.TransactionManager;
                //在源数据库中开始事务处理
                using (Transaction myT = tm.StartTransaction())
                {
                    //打开源数据库中的块表
                    DimStyleTable bt = (DimStyleTable)tm.GetObject(sourceDb.DimStyleTableId, OpenMode.ForRead, false);
                    //遍历每个块
                    foreach (ObjectId btrId in bt)
                    {
                        DimStyleTableRecord btr = (DimStyleTableRecord)tm.GetObject(btrId, OpenMode.ForRead, false);
                        //只加入命名块和非布局块到复制列表中
                        //if (!btr.IsAnonymous && !btr.IsLayout)
                        {
                            blockIds.Add(btrId);
                        }
                        btr.Dispose();
                    }
                    bt.Dispose();
                }
                //定义一个IdMapping对象
                IdMapping mapping = new IdMapping();
                //从源数据库向目标数据库复制块表记录
                sourceDb.Wblock(destDb, blockIds, Point3d.Origin, DuplicateRecordCloning.Ignore);
                //操作完成，销毁源数据库
                sourceDb.Dispose();
            }
            catch (ZwSoft.ZwCAD.Runtime.Exception ex)
            {
                Application.ShowAlertDialog("复制错误: " + ex.Message);
            }  
        }

        public static void OpenDwg(string fileName)
        {
            DocumentCollection acDocMgr = ZwSoft.ZwCAD.ApplicationServices.Application.DocumentManager;

            Document acNewDoc = acDocMgr.Open(fileName, false);     //filepath打开的文件路径，false表示文件可改写
            Database acDbNewDoc = acNewDoc.Database;
            acDocMgr.MdiActiveDocument = acNewDoc;     //将打开的文件设置为当前显示

            /*Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            //获取文档管理器对象以打开Dwg文件
            DocumentCollection docs = Application.DocumentManager;

            //打开所选择的Dwg文件
            Document doc = docs.Open(fileName);
            //设置当前的活动文档为新打开的Dwg文件
            Application.DocumentManager.MdiActiveDocument = doc;
         */
        }

        public static void SaveDwg()
        {
            Document doc = Application.DocumentManager.MdiActiveDocument;
            //DocumentCollection docs = Application.DocumentManager;

            //获取DWGTITLED系统变量，它指示当前图形是否已命名。
            object tiled = Application.GetSystemVariable("DWGTITLED");
            //if (!doc.Saved()) return;//如果图形没有未保存的修改，则返回
            //if (Convert.ToInt16(tiled) == 0)//如果图形没有被命名
                //doc.Database.SaveAs("C:\\test.dwg", DwgVersion.Current);
            //else
            doc.CloseAndSave(doc.Name);//保存当前文档
        }


        public static void ProcessLineType(this Database db)
        {
            using (Transaction tr = db.TransactionManager.StartTransaction())
            {
                // 模型空间
                BlockTable blkTbl = tr.GetObject(db.BlockTableId, OpenMode.ForRead)
                    as BlockTable;
                BlockTableRecord modelSpace = tr.GetObject(
                    blkTbl[BlockTableRecord.ModelSpace], OpenMode.ForRead)
                    as BlockTableRecord;

                // 遍历模型空间
                foreach (ObjectId oid in modelSpace)
                {
                    DBObject dbobj = tr.GetObject(oid, OpenMode.ForWrite);
                    if (dbobj is Entity)
                    {
                        Entity entity = dbobj as Entity;
                        entity.LinetypeScale = 0.1;
                        entity.Dispose();
                       /* doc.Editor.WriteMessage("\nEntity: {0}, {1}, {2}, {3}",
                            entity.Id,
                            entity.GetType().ToString(),
                            entity.Layer,
                            entity.Color.ToString());*/
                    }
                }
            }
        }

        public static void ReadDwgFileTest(string fileName)
        {
            


            Document doc = Application.DocumentManager.MdiActiveDocument;

            using (Database db = new Database(false, true))
            {
                try
                {
                    // 读取dwg文件
                    //string dwgFileFullPath =
                        //@"E:\Temp\F190352-020.dwg";
                    db.ReadDwgFile(fileName,
                        FileShare.ReadWrite, false, "");
                    db.CloseInput(true);



                    Database db2 = new Database(false, true);
                    //读入Dwg文件
                    db2.ReadDwgFile("D:\\TYInstall\\DIMTemplate.dwg", FileShare.Read, true, "");
                    //为了让插入块的函数在多个图形文件打开的情况下起作用，你必须使用下面的函数把Dwg文件关闭
                    
               
                    //把源数据库模型空间中的实体插入到当前数据库的一个新的块表记录中
                    ObjectId btrId = db.Insert("TTL", db2, false);


                    ProcessLineType(db);

                    db2.CloseInput(true);
                    db2.Dispose();



                    //ImportBlocksFromDwg(db, "D:\\TYuan\\DIMTemplate.dwg");
                    //db.Save();
                    //SecurityParameters parm;
                    string saveFileName = ("D:\\");
                    string justNanme = Path.GetFileName(db.Filename);
                    saveFileName = saveFileName + justNanme;
                    db.SaveAs(saveFileName, new SecurityParameters());
                    
                }
                catch (System.Exception ex)
                {
                    doc.Editor.WriteMessage("\nUnable to read drawing file.");
                    return;
                }
                return;
            }
        }
	}
	
}
