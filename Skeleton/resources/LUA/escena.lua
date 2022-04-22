function scene0()
    scene:name("Main menu")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])
    
    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaMenu;
        zOrder: -1
    ]])

    
    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: menuBackground; 
        width: 1280;
        height : 720;
    ]])

    local startButton = scene:createObject("Start Button"):addComponent("Button");
    local exitButton = scene:createObject("Exit Button"):addComponent("Button");

    startButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 300;
		posZ: 1
    ]])

    exitButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 360;
		posZ: 1
    ]])

    local mainmenu = bg:addComponent("MainMenu");
    mainmenu:sendComponent(0, startButton);
    mainmenu:sendComponent(1, exitButton);
end

function scene1()
    scene:name("Escena de Prueba")


    persistentObject:addComponent("ComponenteDeContar")

    local a = scene:createObject("AAA");
    a:addComponent("MoverPantalla"):sendMsg("inicial: 0.1")


	local btest = scene:createObject("btest");
    btest:addComponent("Button"):sendMsg([[
        material: Heal_bg;
        width: 300;
        height: 50;
        posX: 400;
        posY: 100;
    ]]) 	
	
    
	
    local testImagen = scene:createObject("uiobj")
	testImagen:addComponent("Transform")
	testImagen:addComponent("Image"):sendMsg([[
        material: ui
    ]])
	
    --Slider--
	local testSlider = scene:createObject("miSlider")
	testSlider:addComponent("Transform")
    testSlider:addComponent("Slider"):sendMsg([[
        materialBar: Heal;
        materialBarBg: Heal_bg;
        materialButton: CircleButton;
        width: 300;
        height: 50;
        posX: 100;
        posY: 100;
    ]])
    testSlider:addComponent("SaludJugador")

    --Suelo--
	local suelo = scene:createObject("Suelo")
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 100,1,100;
        position: 0,0,0;
        rotation: 0,0,0,0;
    ]])

    local comp3 = suelo:addComponent("Mesh")
    comp3:sendMsg([[
        meshName: cube.mesh;
    ]])
    local compRigidbodySuelo = suelo:addComponent('Rigidbody')
    compRigidbodySuelo:sendMsg([[
        trigger: false;
        state: kinematic;
        mass: 0.0;
        shape: cube; 
        restitution: 0.9;
        colliderScale: 100,1,100;
        ]])

    local material = suelo:addComponent("Material")
    material:sendMsg([[materialName: bolaroja]])
    material:sendComponent(0, comp3)

    --Camara comentada por lo del splash screen
    -- local camara = scene:createObject("CamaritaGuapa")
    -- local transcam = camara:addComponent('Transform')
    -- transcam:sendMsg([[
    --    scale: 1,1,1;
    --    position: 0,40,80;
    --    rotation: 0,0,0,0;
    --]])

    -- local camCamera = camara:addComponent('Camera')
     
    -- camCamera:sendMsg([[
    --    name: escenaJuego;
    --]])

    --Bola--
    local bola = scene:createObject("Bola")
    local compBola = bola:addComponent('Transform')
        
    compBola:sendMsg([[
        scale: 2,2,2;
        position: -20,40,0;
        rotation: 0,0,0,0;
    ]])
    local compBolaMesh = bola:addComponent('Mesh'):sendMsg([[
        meshName: bolaroja.mesh;
    ]])

    local compRigidbody = bola:addComponent('Rigidbody')
    compRigidbody:sendMsg([[
        state: static;
        mass: 1.0;
        shape: sphere; 
        restitution: 1.0;
        colliderScale: 3,3,3;
    ]])

    --BolaPesada--
    local bolaPesada = scene:createObject("BolaPesada")
    local compBolaPesada = bolaPesada:addComponent('Transform')
        
    compBolaPesada:sendMsg([[
        scale: 4,4,4;
        position: 20,40,0;
        rotation: 0,0,0,0;
        colliderScale: 3,3,3;
    ]])
    local compBolaMesh = bolaPesada:addComponent('Mesh'):sendMsg([[
        meshName: sphere.mesh;
    ]])

    local bolaPesadaRigid = bolaPesada:addComponent('Rigidbody')
    bolaPesadaRigid:sendMsg([[
        shape: sphere; 
        mass: 1.0;
        type: static;
        restitution: 0.75;
    ]])

    local luz = scene:createObject("Luz")
    local compLuz = luz:addComponent('Transform')
        
    compLuz:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: -45,0,0,0;
    ]])
    
    local compLight = luz:addComponent('Light')
    compLight:sendMssg([[
        name: luz_direccional
        type: directional
    ]])
----------hijo ogro
    local bolaHijaJug = scene:createObject("BolaHija")
    local compTrBolaHijaJug = bolaHijaJug:addComponent('Transform')
        
    compTrBolaHijaJug:sendMsg([[
        scale: 2,2,2;
        position: 0,10,0;
        rotation: 0,0,0,0;
    ]])
    local compbolaHijaJugMesh = bolaHijaJug:addComponent('Mesh'):sendMsg([[
        meshName: sphere.mesh;
    ]])

    
    local rotarcam = bolaHijaJug:addComponent('CamRotate')
--------------

----------bola hijo ogro "cam"
    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
        
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')
    local camFollow = cam:addComponent('CamFollow')

    camCamera:sendMsg([[
        name: escenaJuego;
    ]])
    
    
    --player--
    local player = scene:createObject("jugador")
    local tr = player:addComponent("Transform")
    tr:sendMsg([[
        scale: 2,2,2;
        position: 0,10,0;
        rotation: 0,0,0,0;
    ]])
    player:addComponent("Rigidbody"):sendMsg([[
        shape: cube; 
        type: dynamic;
        mass: 10.0;
        restitution: 0.75;
        colliderScale: 3,8,2;
    ]])
    local mesh = player:addComponent("Mesh")
    mesh:sendMsg([[meshName: Sinbad.mesh]])
    player:addComponent("MovimientoJugador"):sendMsg([[
        speed: 15.0
        rotSpeed: 5.0
    ]])

    local animation = player:addComponent("Animation")
    animation:sendMsg([[animName: Dance]])

    local luzPlayer = scene:createObject("Luz")
    local compLuzPlayer = luzPlayer:addComponent('Transform')
        
    compLuzPlayer:sendMsg([[
        scale: 1,1,1;
        position: 0,10,0;
        rotation: 0,0,0,0;
    ]])
    compLuzPlayer:sendComponent(1, tr)
    
    local compLightPlayer = luzPlayer:addComponent('Light')
    compLightPlayer:sendMssg([[
        name: luz_point
        type: point
    ]])

     --Enemigo--
    local boss = scene:createObject("boss")
    local bosstr = boss:addComponent("Transform")
    bosstr:sendMsg([[
        scale: 3,3,3;
        position: 50,20,-50;
        rotation: -1.57079633,0,0,0;
    ]])
    local bossAI = boss:addComponent("ComportamientoBoss")
    bossAI:sendComponent(0, tr)
    boss:addComponent("Mesh"):sendMsg([[meshName: boss.mesh]])
    boss:addComponent('Rigidbody'):sendMsg([[
        state: dynamic;
        mass: 10.0;
        shape: sphere; 
        restitution: 1.0;
        colliderScale: 18,18,18;
    ]])

    --haciendo hijo del hijo del player a la  "cam"
    trcam:sendComponent(1, compTrBolaHijaJug)

    --Metiendo componente rotar Camara
    rotarcam:sendMsg([[
        verSens: 5.5
        horiSens: 5.5
    ]])

    camFollow:sendGameObject(0, player)

    rotarcam:sendGameObject(0, boss)
    rotarcam:sendGameObject(1, player)
    rotarcam:sendGameObject(2, cam)

    local particleSys = scene:createObject("Bomba")
    particleSys:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: 0,5,-20; rotation: 0,0,0,0;]])
    local pSys = particleSys:addComponent("ParticleSystem")
    pSys:sendMsg([[particleName: bomb; emitting: true]])

    local lluviaParticle = scene:createObject("Lluvia")
    lluviaParticle:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: 0,100,0; rotation: 0,0,0,0;]])
    local lluviaParticleSys = lluviaParticle:addComponent("ParticleSystem")
    lluviaParticleSys:sendMsg([[particleName: lluvia; emitting: true]])

    local torch = scene:createObject("Lluvia")
    torch:addComponent("Transform"):sendMsg([[scale: 1,1,1; position: -30,10,0; rotation: 0,0,0,0;]])
    local torchSys = torch:addComponent("ParticleSystem")
    torchSys:sendMsg([[particleName: torch; emitting: true]])

    local textPrueba = scene:createObject("TextoPrueba")
    local textPruebaText = textPrueba:addComponent("Text")
    textPruebaText:sendMsg([[
        position: 50, 50, 0;
        fontName: chikory
        mainColor: 0.3, 1.0, 0.6, 1.0;
        textScale: 0.05
        alignment : 0
        ]])

    --textPruebaText:sendString("V I D A S")
    local showText = textPrueba:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.1
    ]])
    showText:sendString("Hola que tal como estas")

    local textPrueba2 = scene:createObject("TextoPrueba2")
    local textPrueba2text = textPrueba2:addComponent("Text")
    textPrueba2text:sendMsg([[
        position: 20, 20, 0;
        fontName: robot
        mainColor: 0.1, 0.2, 0.9, 1.0;
        textScale:0.03
        alignment : 0
        ]])

    textPrueba2text:sendString("Soy el segundo texto uwu")

    local skybox = scene:createObject("Skybox")
    skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxhell; distance: 300; ]])

end


function scene2()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    --obj:addComponent("ComponenteDeContar"):sendMsg("Hola tontatatatata")
    --obj:addComponent("MouseTracker")
    obj:addComponent('EscribirNumero'):sendMsg([[
        numerito: 4;
        otronumerito: 12 
    ]])


     --Suelo--
	local suelo = scene:createObject("Suelo")
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,0,0;
        rotation: 0,0,0,0;
    ]])

    local comp3 = suelo:addComponent("Mesh")
    comp3:sendMsg([[
        meshName: cube.mesh;
    ]])
    local compRigidbodySuelo = suelo:addComponent('Rigidbody')
    compRigidbodySuelo:sendMsg([[
        trigger: true;
        state: kinematic;
        mass: 0.0;
        shape: cube; 
        restitution: 0.9;
        colliderScale: 30,10,30;
        ]])

    local material = suelo:addComponent("Material")
    material:sendMsg([[materialName: bolaroja]])
    material:sendComponent(0, comp3)

    suelo:addComponent("DeadZone")

    --luz
    local luz = scene:createObject("Luz")
    local compLuz = luz:addComponent('Transform')
        
    compLuz:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: -45,0,0,0;
    ]])
    
    local compLight = luz:addComponent('Light')
    compLight:sendMssg([[
        name: luz_direccional
        type: directional
    ]])

    local camara = scene:createObject("CamaritaGuapa")
    local transcam = camara:addComponent('Transform')
    transcam:sendMsg([[
       scale: 1,1,1;
       position: 0,40,80;
       rotation: 0,0,0,0;
    ]])

    local camCamera = camara:addComponent('Camera')
     
    camCamera:sendMsg([[
       name: escenaJuego;
    ]])

local player = scene:createObject("jugador")
local tr = player:addComponent("Transform")
tr:sendMsg([[
    scale: 2,2,2;
    position: 0,10,0;
    rotation: 0,0,0,0;
]])
player:addComponent("Rigidbody"):sendMsg([[
    shape: cube; 
    type: dynamic;
    mass: 10.0;
    restitution: 0.75;
]])
local mesh = player:addComponent("Mesh")
mesh:sendMsg([[meshName: Sinbad.mesh]])
player:addComponent("MovimientoJugador"):sendMsg([[
    speed: 15.0
    rotSpeed: 5.0
]])




end
