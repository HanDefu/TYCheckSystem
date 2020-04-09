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
 *��װ���裺
 *01.�޸�C:\Program Files (x86)\ZWCAD+ 2014\Support\ZWCAD2014.lsp �Զ�����--�޸ķ�ʽ�����Ľ���
 *   ZwManaged.dll ZwDatabaseMgd.dll JigSample.dll ������D:\TYuanĿ¼��
 *02.D:\TYuan\DIMTemplate.dwg���ģ���ļ�
 *03.��Ҫ��D�̸�Ŀ¼ ����ļ� save�������������
 
 * *04.����ע�⣺һ���������ô���ZwManaged.dll ZwDatabaseMgd.dll  �������Ī������Ĵ���
 */
//�Զ����ذ취
//�޸��ļ�
//C:\Program Files (x86)\ZWCAD+ 2014\Support\ZWCAD2014.lsp
//���һ��
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
            ed.WriteMessage("\n��������.");
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

            //ObjectId model = db1.CurrentSpaceId;//ģ�Ϳռ��Id

            using (Transaction trans = db1.TransactionManager.StartTransaction())
            {

                //BlockTable bt = (BlockTable)trans.GetObject(db1.BlockTableId, OpenMode.ForRead);
                //�����ݿ��ģ�Ϳռ����¼����
                BlockTableRecord btr = (BlockTableRecord)trans.GetObject(db1.CurrentSpaceId, OpenMode.ForWrite);

                //btr.GetEnumerator();
                //ѭ������ģ�Ϳռ��е�ʵ��
     

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
            ObjectId blockRefId;//�洢Ҫ����Ŀ���յ�Id
            Database db = spaceId.Database;//��ȡ���ݿ����
            //�Զ��ķ�ʽ�򿪿��
            BlockTable bt = (BlockTable)db.BlockTableId.GetObject(OpenMode.ForRead);
            //���û��blockName��ʾ�Ŀ飬����򷵻�
            if (!bt.Has(blockName)) return ObjectId.Null;
            //��д�ķ�ʽ�򿪿ռ䣨ģ�Ϳռ��ͼֽ�ռ䣩
            BlockTableRecord space = (BlockTableRecord)spaceId.GetObject(OpenMode.ForWrite);
            //����һ������ղ����ò����
            BlockReference br = new BlockReference(position, bt[blockName]);
            br.ScaleFactors = scale;//���ÿ���յ����ű���
            br.Layer = layer;//���ÿ���յĲ���
            br.Rotation = rotateAngle;//���ÿ���յ���ת�Ƕ�
            ObjectId btrId = bt[blockName];//��ȡ����¼��Id
            //�򿪿���¼
            BlockTableRecord record = (BlockTableRecord)btrId.GetObject(OpenMode.ForRead);
            //��ӿ�������֧��
            //if (record.Annotative == AnnotativeStates.True)
            {
                //ObjectContextCollection contextCollection = db.ObjectContextManager.GetContextCollection("ACDB_ANNOTATIONSCALES");
                //ObjectContexts.AddContext(br, contextCollection.GetContext("1:1"));
            }
            blockRefId = space.AppendEntity(br);//�ڿռ��м��봴���Ŀ����
            db.TransactionManager.AddNewlyCreatedDBObject(br, true);//֪ͨ��������봴���Ŀ����
            space.DowngradeOpen();//Ϊ�˰�ȫ�������״̬��Ϊ��
            return blockRefId;//������ӵĿ���յ�Id
        }

        public static void ImportBlocksFromDwg(this Database destDb, string sourceFileName)
        {
            //����һ���µ����ݿ������ΪԴ���ݿ⣬�Զ����ⲿ�ļ��еĶ���
            Database sourceDb = new Database(false, true);
            try
            {
                //��DWG�ļ����뵽һ����ʱ�����ݿ���
                sourceDb.ReadDwgFile(sourceFileName, System.IO.FileShare.Read, true, null);
                //����һ�����������洢���ObjectId�б�
                ObjectIdCollection blockIds = new ObjectIdCollection();
                //��ȡԴ���ݿ�������������
                ZwSoft.ZwCAD.DatabaseServices.TransactionManager tm = sourceDb.TransactionManager;
                //��Դ���ݿ��п�ʼ������
                using (Transaction myT = tm.StartTransaction())
                {
                    //��Դ���ݿ��еĿ��
                    DimStyleTable bt = (DimStyleTable)tm.GetObject(sourceDb.DimStyleTableId, OpenMode.ForRead, false);
                    //����ÿ����
                    foreach (ObjectId btrId in bt)
                    {
                        DimStyleTableRecord btr = (DimStyleTableRecord)tm.GetObject(btrId, OpenMode.ForRead, false);
                        //ֻ����������ͷǲ��ֿ鵽�����б���
                        //if (!btr.IsAnonymous && !btr.IsLayout)
                        {
                            blockIds.Add(btrId);
                        }
                        btr.Dispose();
                    }
                    bt.Dispose();
                }
                //����һ��IdMapping����
                IdMapping mapping = new IdMapping();
                //��Դ���ݿ���Ŀ�����ݿ⸴�ƿ���¼
                sourceDb.Wblock(destDb, blockIds, Point3d.Origin, DuplicateRecordCloning.Ignore);
                //������ɣ�����Դ���ݿ�
                sourceDb.Dispose();
            }
            catch (ZwSoft.ZwCAD.Runtime.Exception ex)
            {
                Application.ShowAlertDialog("���ƴ���: " + ex.Message);
            }  
        }

        public static void OpenDwg(string fileName)
        {
            DocumentCollection acDocMgr = ZwSoft.ZwCAD.ApplicationServices.Application.DocumentManager;

            Document acNewDoc = acDocMgr.Open(fileName, false);     //filepath�򿪵��ļ�·����false��ʾ�ļ��ɸ�д
            Database acDbNewDoc = acNewDoc.Database;
            acDocMgr.MdiActiveDocument = acNewDoc;     //���򿪵��ļ�����Ϊ��ǰ��ʾ

            /*Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            //��ȡ�ĵ������������Դ�Dwg�ļ�
            DocumentCollection docs = Application.DocumentManager;

            //����ѡ���Dwg�ļ�
            Document doc = docs.Open(fileName);
            //���õ�ǰ�Ļ�ĵ�Ϊ�´򿪵�Dwg�ļ�
            Application.DocumentManager.MdiActiveDocument = doc;
         */
        }

        public static void SaveDwg()
        {
            Document doc = Application.DocumentManager.MdiActiveDocument;
            //DocumentCollection docs = Application.DocumentManager;

            //��ȡDWGTITLEDϵͳ��������ָʾ��ǰͼ���Ƿ���������
            object tiled = Application.GetSystemVariable("DWGTITLED");
            //if (!doc.Saved()) return;//���ͼ��û��δ������޸ģ��򷵻�
            //if (Convert.ToInt16(tiled) == 0)//���ͼ��û�б�����
                //doc.Database.SaveAs("C:\\test.dwg", DwgVersion.Current);
            //else
            doc.CloseAndSave(doc.Name);//���浱ǰ�ĵ�
        }


        public static void ProcessLineType(this Database db)
        {
            using (Transaction tr = db.TransactionManager.StartTransaction())
            {
                // ģ�Ϳռ�
                BlockTable blkTbl = tr.GetObject(db.BlockTableId, OpenMode.ForRead)
                    as BlockTable;
                BlockTableRecord modelSpace = tr.GetObject(
                    blkTbl[BlockTableRecord.ModelSpace], OpenMode.ForRead)
                    as BlockTableRecord;

                // ����ģ�Ϳռ�
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
                    // ��ȡdwg�ļ�
                    //string dwgFileFullPath =
                        //@"E:\Temp\F190352-020.dwg";
                    db.ReadDwgFile(fileName,
                        FileShare.ReadWrite, false, "");
                    db.CloseInput(true);



                    Database db2 = new Database(false, true);
                    //����Dwg�ļ�
                    db2.ReadDwgFile("D:\\TYInstall\\DIMTemplate.dwg", FileShare.Read, true, "");
                    //Ϊ���ò����ĺ����ڶ��ͼ���ļ��򿪵�����������ã������ʹ������ĺ�����Dwg�ļ��ر�
                    
               
                    //��Դ���ݿ�ģ�Ϳռ��е�ʵ����뵽��ǰ���ݿ��һ���µĿ���¼��
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
