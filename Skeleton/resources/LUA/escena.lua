-- Escenas del juego: 
--  0: menu
--  1: settings
--  2: pause
--  3: overworld
--  4: boss1
--  5: boss2
--  6: victory
--  7: defeat
--------------
package.path = package.path .. ";../resources/LUA/?.lua"

function scene0() -- Main menu
    --size(randomBetween(100, 1000), randomBetween(100, 1000))
    scene:name("Main menu")
    menu = require "menu";
    menu:cambiarIcono()
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
        material: backgroundMenu; 
        width: 1280;
        height : 720;
    ]])

    local startButton = scene:createObject("Start Button"):addComponent("Button");
    local settingsButton = scene:createObject("Settings Button"):addComponent("Button");
    local exitButton = scene:createObject("Exit Button"):addComponent("Button");

    startButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 300;
		posZ: 1
    ]])

    settingsButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 360;
		posZ: 1
    ]])

    exitButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 420;
		posZ: 1
    ]])

    local mainmenu = bg:addComponent("MainMenu");
    mainmenu:sendComponent(0, startButton);
    --mainmenu:sendComponent(1, settingsButton);
    mainmenu:sendComponent(1, exitButton);
    createVignette()
    
end

function scene1() -- Settings
    scene:name("Settings")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: settings;
        zOrder: -1
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: backgroundMenu; 
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

function scene2() -- Pause
    scene:name("Pause")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: pause;
        zOrder: 2
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: pauseMenu; 
        width: 1280;
        height : 720;
    ]])

    local continue = scene:createObject("Start Button"):addComponent("Button");
    local exitButton = scene:createObject("Exit Button"):addComponent("Button");

    continue:sendMsg([[
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

    local mainmenu = bg:addComponent("PauseMenu");
    mainmenu:sendComponent(0, continue);
    mainmenu:sendComponent(1, exitButton);
    createVignette()
end

function scene3() -- Prueba
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

    -- Slider--
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

    -- Suelo--
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

    -- Camara comentada por lo del splash screen
    -- local camara = scene:createObject("CamaritaGuapa")
    -- local transcam = camara:addComponent('Transform')
    -- transcam:sendMsg([[
    --    scale: 1,1,1;
    --    position: 0,40,80;
    --    rotation: 0,0,0,0;
    -- ]])

    -- local camCamera = camara:addComponent('Camera')

    -- camCamera:sendMsg([[
    --    name: escenaJuego;
    -- ]])

    -- Bola--
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

    -- BolaPesada--
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
        position: 0,80,60;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')
    local camFollow = cam:addComponent('CamFollow')

    camCamera:sendMsg([[
        name: escenaJuego;
    ]])

    -- player--
    local player = scene:createObject("jugador")
    local tr = player:addComponent("Transform")
    tr:sendMsg([[
        scale: 2,2,2;
        position: 0,30,0;
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

    local dashParticles = scene:createObject("dashParticles")
    local trDash = dashParticles:addComponent("Transform")
    trDash:sendMsg([[scale: 1,1,1; position: 0,35,0; rotation: 0,0,0,0;]])
    local dashSys = dashParticles:addComponent("ParticleSystem")
    dashSys:sendMsg([[particleName: dash; emitting: false]])
    trDash:sendComponent(1, tr)

    -- Enemigo--
    local boss = scene:createObject("boss")
    local bosstr = boss:addComponent("Transform")
    bosstr:sendMsg([[
        scale: 15,15,15;
        position: 50,20,-50;
        rotation: -1.57079633,0,0,0;
    ]])
    local bossAI = boss:addComponent("ComportamientoBoss")
    bossAI:sendComponent(0, tr)
    boss:addComponent("Mesh"):sendMsg([[meshName: Boss.mesh]])
    boss:addComponent('Rigidbody'):sendMsg([[
        state: dynamic;
        mass: 10.0;
        shape: sphere; 
        restitution: 1.0;
        colliderScale: 18,18,18;
    ]])


    -- haciendo hijo del hijo del player a la  "cam"
    trcam:sendComponent(1, compTrBolaHijaJug)

    -- Metiendo componente rotar Camara
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

    -- textPruebaText:sendString("V I D A S")
    local showText = textPrueba:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.1
    ]])
    showText:sendString("Hola que tal como estas")
    createText(20, 100, 'tititiitiutututu')
    local dialogue = scene:createObject("Dialogue"):addComponent('Dialogue')
    dialogue:sendMsg("lines: 3")

    for i = 0, 2, 1 do
        local line = createText(20, 500 + i * 30, '  ')
        dialogue:sendComponent(i, line);
    end
    dialogue:sendMssg([[
        line0: #Soy el primer texto uwu#
        line1: #Soy el segundo texto uwu#
        line2: #Soy el tercer texto uwu...#
    ]])
    dialogue:sendMssg([[
        line0: #Soy el cuarto texto uwu#
        line1: #Soy el quinto texto uwu#
        line2: #Soy el sexto texto uwu...#
    ]])
    dialogue:sendMssg([[
        line0: #Hola nene, mi nombre es Yojhan Steven, si estas#
        line1: #viendo esto es porque eres una persona muy#
        line2: #atenta Muchas gracias por tu tiempo.#
    ]])
    -- textPrueba2text:sendString("Soy el segundo texto uwu")

    local skybox = scene:createObject("Skybox")
    skybox:addComponent("Skybox"):sendMsg([[materialName: skyboxhell; distance: 300; ]])

    createVignette()
    scene:createObject("Pause Game"):addComponent("PauseGame")
end

function createText(x, y, text)
    local textObj = scene:createObject("textObj")
    local textComp = textObj:addComponent("Text")
    textComp:sendMsg([[
        position: ]] .. x .. ',' .. y .. [[, 0;
        fontName: SourceSansProLight
        mainColor: 1, 1, 1, 1.0;
        textScale:0.05
        alignment : 0
        ]])
    local showText = textObj:addComponent("ShowText")
    showText:sendMssg([[
        interval: 0.1
        ]])
    showText:sendString(text)
    return showText
end

function scene4() -- Victory
    scene:name("Escena victoria")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaMuerte;
        zOrder: -2
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: menuDeadBackground; 
        width: 1280;
        height : 720;
    ]])

    local restartButton = scene:createObject("Restart Button"):addComponent("Button");
    local menuButton = scene:createObject("Menu Button"):addComponent("Button");

    restartButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 300;
		posZ: 1
    ]])

    menuButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 360;
		posZ: 1
    ]])

    local mainmenu = bg:addComponent("DeadMenu");
    mainmenu:sendComponent(0, restartButton);
    mainmenu:sendComponent(1, menuButton);
    createVignette()
end

function scene5() -- Defeat
    scene:name("Escena derrota")

    local cam = scene:createObject("cam")
    local trcam = cam:addComponent('Transform')
    trcam:sendMsg([[
        scale: 2,2,2;
        position: 0,40,80;
        rotation: 0,0,0,0;
    ]])

    local camCamera = cam:addComponent('Camera')

    camCamera:sendMsg([[
        name: escenaMuerte;
        zOrder: -2
    ]])

    local bg = scene:createObject("Background");
    bg:addComponent("Transform")
    bg:addComponent("Image"):sendMsg([[
        material: menuDeadBackground; 
        width: 1280;
        height : 720;
    ]])

    local restartButton = scene:createObject("Restart Button"):addComponent("Button");
    local menuButton = scene:createObject("Menu Button"):addComponent("Button");

    restartButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 300;
		posZ: 1
    ]])

    menuButton:sendMsg([[
        material: Heal_bg;
        width: 100;
        height: 50;
        posX: 500;
        posY: 360;
		posZ: 1
    ]])

    local mainmenu = bg:addComponent("DeadMenu");
    mainmenu:sendComponent(0, restartButton);
    mainmenu:sendComponent(1, menuButton);
    createVignette()
end


function createVignette()
    scene:createObject('Vignette'):addComponent('Image'):sendMssg([[
        material: splashScreen_vignette; width: 1280; height : 720; posZ: 20
    ]])
end
