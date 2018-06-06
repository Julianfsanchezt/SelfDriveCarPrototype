import cv2
import numpy as np
MIN_MATCH_COUNT=30
font = cv2.FONT_HERSHEY_SIMPLEX
detector=cv2.xfeatures2d.SIFT_create()

FLANN_INDEX_KDITREE=0
flannParam=dict(algorithm=FLANN_INDEX_KDITREE,tree=5)
#Fast Approximate Nearest Neighbor Search Library 
flann=cv2.FlannBasedMatcher(flannParam,{})

img1=cv2.imread("C:\Users\Julian Felipe\Desktop\senal1.jpg",0)
KeyPointsImg1,DescriptoresImg1=detector.detectAndCompute(img1,None)

cam=cv2.VideoCapture(0)
Contprueba = 0
ContAciertos = 0
ContIdSign = 0
identificados = 0
aciertosParciales = 0
aciertoTotal = 0	#variable que incrementa en 1 si el acierto es contundente
IdSignificativa = 0	#variable que incrementa en 1 si la deteccion es significativa pero no necesariamente plena
print("# Prueba\t Identificacion Significativa\t Aciertos")
while Contprueba < 150:

    ret, Camara=cam.read()
    CamaraGray=cv2.cvtColor(Camara,cv2.COLOR_BGR2GRAY)
	
	#Deteccion de Keypoints y descriptores de la imagen en vivo de la camara.
    KeyPointsCamara,DescriptoresCamara=detector.detectAndCompute(CamaraGray,None)
    matches=flann.knnMatch(DescriptoresCamara,DescriptoresImg1,k=2)

    goodMatch=[]
    for m,n in matches:
        if(m.distance<0.75*n.distance):
            goodMatch.append(m)
           
    if(len(goodMatch)>MIN_MATCH_COUNT):
        tp=[]
        qp=[]
        for m in goodMatch:
            tp.append(KeyPointsImg1[m.trainIdx].pt)
            qp.append(KeyPointsCamara[m.queryIdx].pt)

        tp,qp=np.float32((tp,qp))
        H,status=cv2.findHomography(tp,qp,cv2.RANSAC,3.0)
        h,w=img1.shape
        trainBorder=np.float32([[[0,0],[0,h-1],[w-1,h-1],[w-1,0]]])
        queryBorder=cv2.perspectiveTransform(trainBorder,H)
        cv2.putText(Camara,'GIRO A LA DERECHA',(20,400), font, 0.5,(0,255,0),1,cv2.LINE_AA)
        
        cv2.polylines(Camara,[np.int32(queryBorder)],True,(0,255,0),5)
        aciertos = 1
        
        
    else:
    	aciertos = 0
    	ContIdSign += 1
        
    ContAciertos+=aciertos
    Contprueba += 1
    print("     "+str(Contprueba)+"\t"+"                "+str(identificados)+"\t"+"                   "+str(aciertos)+"\t")
    cv2.imshow('Salida de Video',Camara)
    if cv2.waitKey(10)==ord('q'):
        break
cam.release()
cv2.destroyAllWindows()
print("Cantidad de Pruebas: "+str(Contprueba))
print("Cantidad de Detecciones plenas: "+str(ContAciertos))
print("Cantidad de Detecciones no plenas: "+str(ContIdSign))
print("Efectividad: "+str(ContAciertos)+"/"+str(Contprueba)+" - "+str((ContAciertos * 100)/Contprueba)+"%")

