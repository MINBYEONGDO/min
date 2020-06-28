
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System.Text;

[SerializeField]
public class Data
{
    [SerializeField] public List<int> ScoreList = new List<int>();
}
public class JsonData : MonoBehaviour
{
    public static Data data;
    public static void SaveScore(List<int> list)
    {
        string filepath = Application.dataPath + "/data.json";
        Data data = new Data();
        data.ScoreList = list;
        data.ScoreList = ScoreSort(data.ScoreList);
        string str = JsonUtility.ToJson(data, prettyPrint: true);
        File.WriteAllText(filepath, str);
    }
    public static List<int> ScoreSort(List<int> list)//정렬
    {
        list.Sort();
        list.Reverse();
        while (list.Count >= 6)
        {
            list.RemoveAt(list.Count - 1);
            //list.RemoveAt(6);//왜 에러가 뜬걸까?
        }
        return list;
    }
    public static List<int> LoadScore()
    {
        string filepath = Application.dataPath + "/data.json";
        Data Data = new Data();
        Data = null;
        if (File.Exists(filepath) == true)
        {
            string jsonstr = File.ReadAllText(filepath);
            Data = JsonUtility.FromJson<Data>(jsonstr);
        }
        return Data.ScoreList;
    }

}
//remove와 removeat의 차이
//jsonUtility
//직렬화