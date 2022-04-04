function escenaEjemplo()
    IvanTontoTonto()
end

function scene0()
    scene:name("Escena de Prueba")
    
    local suelo = scene:createObject("Suelo")
	
    local kaka = scene:createObject("uiobj")
	local compdadad2 = kaka:addComponent("Transform")
	local micompo2 = kaka:addComponent("Image"):sendMsg([[
        material: ui
    ]])
	
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,0,0;
        rotation: 0,0,0,0;
    ]])

    local comp3 = suelo:addComponent("Mesh"):sendMsg([[
        meshName: cube.mesh;
    ]])
    local compRigidbodySuelo = suelo:addComponent('Rigidbody')
    compRigidbodySuelo:send2(0, 0.0)
    compRigidbodySuelo:sendMsg([[forma: cube; restitution: 0.9;]])

    local camaraAidaLaMejor = scene:createObject("CamaritaGuapa")
    local compAidaLaMejor = camaraAidaLaMejor:addComponent('Transform')
    camaraAidaLaMejor:addComponent("MouseTracker"):send3(0, 1, nil)
    compAidaLaMejor:sendMsg([[
        scale: 1,1,1;
        position: 0,15,75;
        rotation: 0,0,0,0;
    ]])
    local compAidaLaMejor2 = camaraAidaLaMejor:addComponent('Camera')
   
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
    compRigidbody:send2(1, 1.0)
    compRigidbody:sendMsg([[
        forma: sphere; 
        restitution: 1.0;
    ]])

    local bolaPesada = scene:createObject("BolaPesada")
    local compBolaPesada = bolaPesada:addComponent('Transform')
        
    compBolaPesada:sendMsg([[
        scale: 4,4,4;
        position: 20,40,0;
        rotation: 0,0,0,0;
    ]])
    local compBolaMesh = bolaPesada:addComponent('Mesh'):sendMsg([[
        meshName: sphere.mesh;
    ]])

    local bolaPesadaRigid = bolaPesada:addComponent('Rigidbody')
    bolaPesadaRigid:send2(1, 1.0)
    bolaPesadaRigid:sendMsg([[
        forma: sphere; 
        restitution: 0.75;
    ]])

    local luz = scene:createObject("Luz")
    local compLuz = luz:addComponent('Transform')
        
    compLuz:sendMsg([[
        scale: 1,1,1;
        position: 0,40,0;
        rotation: 0,0,0,0;
    ]])

    local compLight = luz:addComponent('Light')
    compLight:send2(1, 0.0)

   local player = scene:createObject("jugador")
   local tr = player:addComponent("Transform")
   tr:sendMsg([[
    scale: 2,2,2;
    position: 0,11,0;
    rotation: 0,0,0,0;
    ]])
    local mesh = player:addComponent("Mesh")
    mesh:sendMsg([[meshName: Sinbad.mesh]])
    player:addComponent("MovimientoJugador"):sendMsg([[
        speed: 15.0
        rotSpeed: 5.0
    ]])

end


function scene1()
    scene:name("Escena de Dani")
    local obj = scene:createObject("Objeto de Dani")
    --obj:addComponent("ComponenteDeContar"):sendMsg("Hola tontatatatata")
    --obj:addComponent("MouseTracker")
    obj:addComponent('EscribirNumero'):sendMsg([[
        numerito: 4;
        otronumerito: 12 
    ]])
end

function scene2()
    scene:name("Escena de Daniel")
    
    local suelo = scene:createObject("Suelo")
    local comp = suelo:addComponent("EscribirNumero")
    local comp2 = suelo:addComponent("Transform")
    
    comp2:sendMsg([[
        scale: 50,1,50;
        position: 0,-100,0;
        rotation: 0,0,0,0;
    ]])
    local comp3 = suelo:addComponent("Mesh"):sendMsg([[
        meshName: cube.mesh;
    ]])

    local camaraAidaLaMejor = scene:createObject("CamaritaGuapa")
    local compAidaLaMejor = camaraAidaLaMejor:addComponent("Transform")
        
    compAidaLaMejor:sendMsg([[
        scale: 1,1,1;
        position: 0,10,50;
        rotation: 0,0,0,0;
    ]])
    local compAidaLaMejor2 = camaraAidaLaMejor:addComponent("Camera")
   

    -- local comp4 = suelo:addComponent("Rigidbody")
end

-- function scene2()
--     scene::name("Calvo cabron")
--     -- local suelo = scene:createObject("Suelo")
--     -- local comp = suelo:addComponent("EscribirNumero")
--     -- local comp2 = suelo:addComponent("Transform")
    
--     -- local comp3 = suelo:addComponent("Mesh"):sendMsg([[
--     --     meshName: cube.mesh
--     -- ]])
--     -- local comp4 = suelo:addComponent("Rigidbody")
--     comp4:
-- end