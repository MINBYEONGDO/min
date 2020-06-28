
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour
{
    public GameObject[] groups;//유니티에서 가져올 오브젝트 배열
    bool m_bFirstTime = true;//처음 작동한것을 확인하기 위한것
    int[] GroupNumber = new int[2];//현재와 다음 내려올 그룹의 번호를 저장할 공간
    //public int[] GroupNumber;
    void Start()
    {
        NewSpawn();
    }

    public void NewSpawn()
    {
        if (m_bFirstTime == true)//처음일때
        {
            for (int i = 0; i < 2; i++)
            {
                GroupNumber[i] = Random.Range(0, groups.Length);//Random함수로 그룹넘버배열에 숫자 설정
            }
            m_bFirstTime = false;
        }
        else//처음 이후
        {
            GroupNumber[0] = GroupNumber[1];//다음차례의 번호를 이번차례번호에 저장
            GroupNumber[1] = Random.Range(0, groups.Length);//다음차례에 새로운 번호 설정
        }
        Instantiate(groups[GroupNumber[0]], transform.position, Quaternion.identity);
        UIManager.instance.NextGroup(GroupNumber[1]);
        //Instantiate함수
        //게임을 실행하는 도중에 게임오브젝트를 생성하는 함수
        //Instantiate(GameObject original, Vector3 position, Quaternion rotation);
        //1.GameObject original
        //- 생성하고자 하는 게임오브젝트명
        //2.Vector3 position
        //- Vecto3으로 생성될 위치를 설정
        //3.Quaternion rotation
        //생성될 게임 오브젝트의 회전값
        //기본값 ->Quaternion.identity
        //게임오브젝트에서 설정된 회전값 -> GameObject이름.transform.rotation

        //Instantiate로 생성한 오브젝트 제거
        //Destroy함수 사용
        //Destroy(GameObject이름)
        //->게임오브젝트 삭제
        //Destroy(GameObject이름, float time);
        //->time만큼 지연 후 삭제
    }
}